#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main() {
	// map two swap-backed pages
	auto *page0 = (char *) vm_map(nullptr, 0);
	auto *page1 = (char *) vm_map(nullptr, 0);

	// write the filename into virtual memory
	auto *filename = page0 + VM_PAGESIZE - 4;
	std::strcpy(filename, "lampson83.txt");

	// map a file-backed page
	auto *page2 = (char *) vm_map(filename, 0);

	for (unsigned int i=0; i<1930; i++) {
    cout << page2[i];
  }
}
