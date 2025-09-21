#include <iostream>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include "vm_app.h"

using std::cout;


int main() { 
	/* 4 pages of physical memory in the system */
	pid_t x = fork();
	cout << x << std::endl;
	if (x != 0) { // parent
		auto *page0 = static_cast<char *>(vm_map("lampson83.txt", 1));
		auto *page1 = static_cast<char *>(vm_map("lampson83.txt", 0));
		auto *page2 = static_cast<char *>(vm_map("lampson83.txt", 2));
		auto *page3 = static_cast<char *>(vm_map("lampson83.txt", 1));
		auto *page4 = static_cast<char *>(vm_map("lampson83.txt", 1));
		auto *page5 = static_cast<char *>(vm_map("lampson83.txt", 1));
		auto *page6 = static_cast<char *>(vm_map("lampson83.txt", 1));
		// page0[0] = page1[0] = page2[0] = 'a';
    // page3[0] = 'b';
		cout << "test1" << std::endl;
		cout << page3 << std::endl;
		cout << page1 << std::endl;
	} 
	else { // child
		auto *page0 = static_cast<char *>(vm_map(nullptr, 0));
		std::strcpy(page0, "hello world!\n");
		cout << page0;
	}
}
