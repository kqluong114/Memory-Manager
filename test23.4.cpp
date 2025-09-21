#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main() {
	// allocate swap-backed page
	char* swap_page = static_cast<char*>(vm_map(nullptr, 0));
	strcpy(swap_page, "hello from parent");

	// allocate file-backed page
	char* filename = static_cast<char*>(vm_map(nullptr, 0));
	strcpy(filename, "lampson83.txt");
	char* file_page = static_cast<char*>(vm_map(filename, 0));
	vm_yield();
	strcpy(file_page, "data from file");

	// fork a child process
	pid_t child_pid = fork();
	vm_yield();
	if (child_pid == 0) {
		// child process
		cout << "child process:\n";
		cout << "swap page: " << swap_page << std::endl;
		cout << "file page: " << file_page << std::endl;

		// modify swap-backed page in child
		strcpy(swap_page, "modified by child");
		cout << "swap page (modified): " << swap_page << std::endl;
	}
	else {
		// parent process
		cout << "parent process:\n";
		cout << "swap page: " << swap_page << std::endl;
		cout << "file page: " << file_page << std::endl;

		// modify file-backed page in parent
		strcpy(file_page, "modified by parent");
		cout << "file page (modified): " << file_page << std::endl;
	}
	pid_t x = fork();
	cout << x << std::endl;
	exit(0);
	vm_yield();
	if (x != 0) { // parent
		auto *page02 = static_cast<char *>(vm_map("lampson83.txt", 1));
		auto *page12 = static_cast<char *>(vm_map("lampson83.txt", 0));
		auto *page22 = static_cast<char *>(vm_map("lampson83.txt", 2));
		auto *page32 = static_cast<char *>(vm_map("lampson83.txt", 1));
		// page0[0] = page1[0] = page2[0] = 'a';
    // page3[0] = 'b';
		exit(0);
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