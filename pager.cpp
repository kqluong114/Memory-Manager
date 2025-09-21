#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <cstring>
#include <string>
#include <utility>
#include <map>
#include <unordered_map>
#include "vm_pager.h"
#include "globals.h"

void vm_init(unsigned int memory_pages, unsigned int swap_blocks) {
	max_swap_size = int(swap_blocks);
	mem_pages = int(memory_pages);
	zero_page = static_cast<char*>(vm_physmem);
	std::memset(zero_page, 0, VM_PAGESIZE);
	valid_vec.resize(mem_pages, 0);
	valid_vec[0] = 1;
	swap_space.resize(max_swap_size, 0);
}

int vm_create(pid_t parent_pid, pid_t child_pid) {
	processes[child_pid].pid = child_pid;
	return 0;
}

void vm_switch(pid_t pid) {
	curr_process = pid;
	processes[curr_process].pid = pid;
	page_table_base_register = &processes[curr_process].base[0];
}

void* vm_map(const char* filename, unsigned int block) {
	char* new_page_addr = get_next();
	if (new_page_addr == nullptr){
		return nullptr;
	}
	// swap backed
	if (filename == nullptr){
		// if swap space full, return null
		if (int(curr_swap_size) >= max_swap_size){
			return nullptr;
		}
		VirtualPage new_page;
		new_page.pid = processes[curr_process].pid;
		new_page.pt_idx = processes[curr_process].page_table.size();
		Block b;
		blocks.push(b);
		Block* b1 = &blocks.back();
		b1->page_refs.push_back(std::make_pair(processes[curr_process].pid, new_page.pt_idx));
		int j = swap_space_add(b1);
		new_page.block = b1;
		new_page.block->swap_addr = -1;
		new_page.block->resident = 1;
		new_page.file_backed = 0;
		update_pte(*b1, 0, 1, 0);

		new_page.block->file_block = std::make_pair("", j);
		new_page.v_addr = new_page_addr;
		page_table_entry_t i{0, 1, 0};
		processes[curr_process].base[processes[curr_process].page_table.size()] = i;
		processes[curr_process].page_table.push_back(new_page);
	}
	
	// file-backed
	else {
		const char* arena_end = reinterpret_cast<const char*>(VM_ARENA_BASEADDR) + VM_ARENA_SIZE;
		if (filename < reinterpret_cast<const char*>(VM_ARENA_BASEADDR) || filename >= arena_end) {
			return nullptr;
		}

		// reading in filename from the given address
		kernel_filename_str = "";
		const char* str_ptr = filename;
		while (true) {
			char c;
			if (str_ptr >= arena_end) {
				break;
			}
			unsigned int vpn = get_vpn(str_ptr);
			if (!processes[curr_process].base[vpn].read_enable) {
				int q = vm_fault(filename, 0);
				if (q == -1){
					return nullptr;
				}
			}
			char* phys_addr = reinterpret_cast<char*>(vm_physmem) + (processes[curr_process].base[vpn].ppage * VM_PAGESIZE) + get_offset(str_ptr);
			c = *phys_addr;
			if (c == '\0') {
				break; // end of string
			}
			kernel_filename_str += c;
			str_ptr++;
		}

		// if the current block in the file hasn't been created, initialize it
		auto pair1 = std::make_pair(kernel_filename_str, block);
		Block* block1 = file_space[pair1];
		VirtualPage new_page;
		if (!block1) {
			Block b;
			blocks.push(b);
			file_space[pair1] = &blocks.back();
			block1 = &blocks.back();
			block1->file_block = pair1;
			block1->pte = {0, 0, 0};
			new_page.block->resident = 0;
		}

		new_page.pt_idx = processes[curr_process].page_table.size();
		new_page.file_backed = 1;
		block1->page_refs.push_back(std::make_pair(processes[curr_process].pid, new_page.pt_idx));
		new_page.block = block1;	
		new_page.v_addr = new_page_addr;

		processes[curr_process].base[processes[curr_process].page_table.size()] = block1->pte;
		processes[curr_process].page_table.push_back(new_page);
		update_pte(*block1, block1->pte.ppage, block1->pte.read_enable, block1->pte.write_enable);
	}

	// return address of newly-created page
	return reinterpret_cast<void*>(new_page_addr);
}


int vm_fault(const void* addr, bool write_flag) {
	VirtualPage* vpage = nullptr;
	int vpn = get_vpn(addr);
	vpage = &processes[curr_process].page_table[vpn];
	if (vpage == nullptr) {
		return -1;
	}
	
	// update the resident bit if in physmem
	int idx = clock_find(*vpage);
	if (idx != -1) {
		clock_queue[idx].second = 1;
	}

	// if not resident, add into physmem
	if (!vpage->block->resident) {
		int z = phys_add(*vpage);
		if (z == -1) {
			return -1;
		}
		vpage->block->resident = 1;
	}

	// read fault and read disabled
	if (!write_flag && !processes[curr_process].base[vpn].read_enable) {
		update_pte(*vpage->block, -1, 1, -1);
		// if dirty bit is 1, update write bit as well
		if (vpage->block->dirty) {
			update_pte(*vpage->block, -1, -1, 1);
		}
	}

	// write fault and write disabled
	if (write_flag && !processes[curr_process].base[vpn].write_enable) {
		// if zero page
		if (!vpage->file_backed && vpage->block->swap_addr == -1) {
			update_pte(*vpage->block, -1, 1, 1);
			vpage->block->dirty = 1;
			int z = phys_add(*vpage);
			if (z == -1) {
				return -1;
			}
			vpage->block->resident = 1;
		}
		else {
			update_pte(*vpage->block, -1, 1, 1);
			vpage->block->dirty = 1;
		}
	}
	return 0;
}

void vm_destroy() {
	for (VirtualPage& page : processes[curr_process].page_table) {
		// clock queue
		if (page.block->resident) {
			if (!page.file_backed) {
				int ppage1 = page.block->pte.ppage;
				valid_vec[ppage1] = 0; // mark phys page as free

				// remove page from clock queue if swap-backed
				for (auto it = clock_queue.begin(); it != clock_queue.end(); ++it) {
					if (it->first == page) {
						clock_queue.erase(it);
						break;
					}
				}
			}
		}

		// free swap blocks
		if (!page.file_backed && page.block->swap_idx != -1) {
			swap_space[page.block->swap_idx] = nullptr; // mark the swap block as free
			curr_swap_size--;
		}
	}
	processes[curr_process].page_table.clear();
	processes.erase(curr_process);
}