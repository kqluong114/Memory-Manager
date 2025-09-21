#include <iostream>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include "vm_app.h"

using std::cout;


int main() { 
	/* 4 pages of physical memory in the system */
	// if (fork() != 0) { // parent
		auto *page0 = static_cast<char *>(vm_map(nullptr, 0));
		auto *page1 = static_cast<char *>(vm_map(nullptr, 0));
		auto *page2 = static_cast<char *>(vm_map(nullptr, 0));
		auto *page3 = static_cast<char *>(vm_map(nullptr, 0));
		std::strcpy(page0, "lampson83.txt");
		std::strcpy(page1, "lampson83.txt");
		std::strcpy(page2, "lampson83.txt");
		std::strcpy(page3, "lampson83.txt");


		// page0[0] = page1[0] = page2[0] = 'a';
	// } 
	// else { // child
	// 	auto *page0 = static_cast<char *>(vm_map(nullptr, 0));
	// 	std::strcpy(page0, "Hello, world!");
	// }
}
