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
	if (!fork()) { // parent
		auto *fb_page = static_cast<char *>(vm_map(filename, 0));
		fb_page[0] = 'B';
		vm_yield();
	} else { // child
		auto *fb_page = static_cast<char *>(vm_map(filename, 0));
		// assert(fb_page[0] == 'B');
		fb_page[0] = 'H';
	}
		char* swap_page2 = static_cast<char*>(vm_map(nullptr, 0));
	strcpy(swap_page2, "hello from parent");

	// allocate file-backed page
	char* filename2 = static_cast<char*>(vm_map(nullptr, 0));
	strcpy(filename2, "lampson83.txt");
	char* file_page2 = static_cast<char*>(vm_map(filename, 0));
	vm_yield();
	strcpy(file_page2, "data from file");

	// fork a child process
	pid_t child_pid = fork();
	vm_yield();
	if (child_pid == 0) {
		// child process
		cout << "child process:\n";
		cout << "swap page: " << swap_page2 << std::endl;
		cout << "file page: " << file_page2 << std::endl;

		// modify swap-backed page in child
		strcpy(swap_page2, "modified by child");
		cout << "swap page (modified): " << swap_page2 << std::endl;
	}
	else {
		// parent process
		cout << "parent process:\n";
		cout << "swap page: " << swap_page2 << std::endl;
		cout << "file page: " << file_page2 << std::endl;

		// modify file-backed page in parent
		strcpy(file_page2, "modified by parent");
		cout << "file page (modified): " << file_page2 << std::endl;
	}
	pid_t x = fork();
	cout << x << std::endl;
	vm_yield();
	if (x != 0) { // parent
		auto *page02 = static_cast<char *>(vm_map("lampson83.txt", 1));
		auto *page12 = static_cast<char *>(vm_map("lampson83.txt", 0));
		auto *page22 = static_cast<char *>(vm_map("lampson83.txt", 2));
		auto *page32 = static_cast<char *>(vm_map("lampson83.txt", 1));
		// page0[0] = page1[0] = page2[0] = 'a';
    // page3[0] = 'b';
		cout << "test1" << std::endl;
		cout << page32 << std::endl;
		cout << page12 << std::endl;
	}
	else { // child
		auto *page02 = static_cast<char *>(vm_map(nullptr, 0));
		std::strcpy(page02, "hello world!\n");
		cout << page02;
	}
	vm_yield();

	return 0;
}
