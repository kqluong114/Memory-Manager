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
const int MAX_PAGES_IN_ARENA = VM_ARENA_SIZE / VM_PAGESIZE;

// main metadata that is pointed to by vpages
struct Block {
	int dirty = 0;
	int resident = 0;
	page_table_entry_t pte;
	std::pair<std::string, unsigned int> file_block;
	int swap_addr = 0;		// -1 if zero page
	int swap_idx = -1;
	std::vector<std::pair<pid_t, int>> page_refs;
};

// contains data on current process and page table
// points to a block in a file
struct VirtualPage {
	pid_t pid;
	int pt_idx = 0;
	int file_backed = 0;
	char* v_addr;
	Block* block;

	bool operator==(const VirtualPage &rhs) const {
		return (pid == rhs.pid && pt_idx == rhs.pt_idx);
	}
};

// process meta data including page table
struct Process {
	pid_t pid = 0;
	std::vector<VirtualPage> page_table;
	page_table_entry_t base[MAX_PAGES_IN_ARENA];

	bool operator==(const Process &rhs) const {
		return pid == rhs.pid;
	}
};

// hashing used for unordered maps of <string, int> pairs
struct PairHash {
	size_t operator()(const std::pair<std::string, int>& p) const {
		size_t hash1 = std::hash<std::string>{}(p.first);
		size_t hash2 = std::hash<int>{}(p.second);
		return hash1 ^ (hash2 << 1);
	}
};

void update_pte(Block &b, int ppage, int read_bit, int write_bit);
int get_vpn(const void* v_addr);
int get_offset(const void* v_addr);
bool phys_is_full();
void clock_add(VirtualPage &page);
VirtualPage evict_next(VirtualPage &page);
bool page_table_full();
char* get_next();
int clock_find(VirtualPage page);
int phys_add(VirtualPage &page);
int swap_space_add(Block* block);

extern const int MAX_PAGES_IN_ARENA;
extern int mem_pages;
extern int max_swap_size;
extern int curr_swap_size;
extern std::vector<Block*> swap_space;
extern int curr_process;
extern char* zero_page;
extern std::unordered_map<pid_t, Process> processes;
extern std::unordered_map<std::pair<std::string, unsigned int>, Block*, PairHash> file_space;
extern std::deque<std::pair<VirtualPage, int>> clock_queue;
extern std::queue<Block> blocks;
extern std::vector<int> valid_vec;
extern int clock_idx;
extern int clock_size;
extern std::string kernel_filename_str;
