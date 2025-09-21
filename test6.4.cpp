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
	strcpy(file_page, "data from file");

	// fork a child process
	pid_t child_pid = fork();

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

	return 0;
}