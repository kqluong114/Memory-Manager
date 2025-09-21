#include <iostream>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include "vm_app.h"

using std::cout;


int main() { /* 4 pages of physical memory in the system */
	auto *filename = static_cast<char *>(vm_map(nullptr, 0));
	std::strcpy(filename, "lampson83.txt");
	if (fork()) { // parent
		auto *fb_page = static_cast<char *>(vm_map(filename, 0));
		fb_page[0] = 'B';
		vm_yield();
	} else { // child
		auto *fb_page = static_cast<char *>(vm_map(filename, 0));
		assert(fb_page[0] == 'B');
		fb_page[0] = 'H';
	}
}
