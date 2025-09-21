#include "globals.h"

int mem_pages = 0;
int max_swap_size = 0;
int curr_swap_size = 0;
char* zero_page = nullptr;
int clock_idx = 0;
std::vector<Block*> swap_space;
int curr_process;
std::unordered_map<pid_t, Process> processes;
std::unordered_map<std::pair<std::string, unsigned int>, Block*, PairHash> file_space;
std::deque<std::pair<VirtualPage, int>> clock_queue;
std::queue<Block> blocks;
std::vector<int> valid_vec;
std::string kernel_filename_str;

// handles updating pte across multiple file-backed pages w/ the same block
// robust enough to work for swap-backed pages
// input -1 if the bits don't change
void update_pte(Block &b, int ppage, int read_bit, int write_bit) {
	// update the block's pte
	if (read_bit != -1) {
		b.pte.read_enable = read_bit;
	}
	if (write_bit != -1) {
		b.pte.write_enable = write_bit;
	}
	if (ppage != -1) {
		b.pte.ppage = ppage;
	}

	// update all associated file-backed pages' pte
	for (const auto& page_ref : b.page_refs) {
		pid_t pid = page_ref.first;
		int pt_idx = page_ref.second;

		Process &process = processes[pid];
		page_table_entry_t &pte = process.base[pt_idx];

		if (read_bit != -1) {
			pte.read_enable = read_bit;
		}
		if (write_bit != -1) {
			pte.write_enable = write_bit;
		}
		if (ppage != -1) {
			pte.ppage = ppage;
		}
	}
}

// get virtual page number
int get_vpn(const void* v_addr) {
	char* addr = (char*)v_addr;
	return (addr - reinterpret_cast<char*>(VM_ARENA_BASEADDR)) / VM_PAGESIZE;
}

// get offset in a virtual page
int get_offset(const void* v_addr) {
	char* addr = (char*)v_addr;
	return (addr - reinterpret_cast<char*>(VM_ARENA_BASEADDR)) % VM_PAGESIZE;
}

// true if physmem is full
bool phys_is_full(){
	if (int(clock_queue.size()) >= mem_pages - 1) {
		return true;
	}
	return false;
}

// add page to the back of the clock_queue
void clock_add(VirtualPage &page){
	if (phys_is_full()){
		return;
	}
	clock_queue.push_back(std::make_pair(page, 1));
	return;
}

// assumes phys_mem is full
// returns the page evicted
// modifies the clock by replacing the evicted page
VirtualPage evict_next(VirtualPage &page) {
	while (true) {
		auto it = clock_queue.begin();
		std::pair<VirtualPage, int> &curr = *it;
		if (curr.second == 1) {
			curr.second = 0;
			update_pte(*curr.first.block, -1, 0, 0);
			clock_queue.push_back(curr);
			clock_queue.pop_front();
		}
		else {
			std::pair<VirtualPage, int> prev = curr;
			curr.second = 1;
			curr.first = page;
			update_pte(*curr.first.block, prev.first.block->pte.ppage, -1, -1);
      clock_queue.push_back(curr);
			clock_queue.pop_front();
			return prev.first;
		}
	}
}

// returns true if page table is full
bool page_table_full(){
	return int(processes[curr_process].page_table.size()) == MAX_PAGES_IN_ARENA;
}

// returns the next address available in page table
char* get_next(){
	if (!page_table_full()){
		return reinterpret_cast<char*>(reinterpret_cast<char*>(VM_ARENA_BASEADDR) + processes[curr_process].page_table.size() * VM_PAGESIZE);
	}
	return nullptr;
}

// returns -1 if not found and the index in the clock if found
int clock_find(VirtualPage page) {
	int idx = 0;
	for (const auto& entry : clock_queue) {
		if (entry.first.block == page.block) {
			return idx;
		}
		++idx;
	}
	return -1;
}

// puts a page into phys_mem
int phys_add(VirtualPage &page){
	// get next availale spot in physmem 
  int spot = -1;	// index in physmem to put the page into
	for (int i = 1; i < int(valid_vec.size()); i++) {
		if (valid_vec[i] == 0) {
			spot = i;
			break;
		}
	}

	// no free space in physmem, run clock and evict
	VirtualPage evicted_page;
	evicted_page.pt_idx = -1;
	if (spot == -1) {
		// run the clock
		evicted_page = evict_next(page);
    // change spot to the evicted page's ppage
		spot = evicted_page.block->pte.ppage;
		valid_vec[spot] = 0;
		update_pte(*evicted_page.block, 0, 0, 0);
		evicted_page.block->resident = 0;
	}

	valid_vec[spot] = 1;
	update_pte(*page.block, spot, -1, -1);

	// if a page has not been evicted, that means there is space in the clock
	// this will run if the clock is not full
	if (evicted_page.pt_idx == -1) {
		clock_add(page);
	}

	// if there is an evicted page, and it's dirty then file_write
	else if (evicted_page.block->dirty == 1) {
		const char* filename1 = nullptr;
		unsigned int block1 = evicted_page.block->file_block.second;
		if (evicted_page.file_backed) {
			filename1 = evicted_page.block->file_block.first.c_str();
		}
		void* buf = reinterpret_cast<void*>(reinterpret_cast<char*>(vm_physmem) + spot * VM_PAGESIZE);
		evicted_page.block->dirty = 0;
		file_write(filename1, block1, buf);
	}

	// if the page is swap-backed and is a zero page 
	if (!page.file_backed && page.block->swap_addr == -1) {
		char* dest = static_cast<char*>(reinterpret_cast<char*>(vm_physmem) + spot * VM_PAGESIZE);
		char* src = reinterpret_cast<char *>(vm_physmem);
		std::memcpy(dest, src, VM_PAGESIZE);
		page.block->swap_addr = 0;
		return 0;
	}

	// read page and put into physmem
	unsigned int block = page.block->file_block.second;
	char* buf = reinterpret_cast<char*>(reinterpret_cast<char*>(vm_physmem) + page.block->pte.ppage * VM_PAGESIZE);
	int z = file_read(page.file_backed ?  page.block->file_block.first.c_str() : nullptr, block, buf);
	if (z == -1){
		return -1;
	}

	return 0;
}

int swap_space_add(Block* block) {
	for(int i = 0; i < int(swap_space.size()); i++) {
		if (!swap_space[i]) {
			swap_space[i] = block;
			// block->swap_addr = 0;
			block->swap_idx = i;
			curr_swap_size++;
			// break;
			return i;
		}
	}
	return -1;
}