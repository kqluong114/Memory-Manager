#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main() {
	auto *page0 = (char *) vm_map(nullptr, 0);
	auto *page1 = (char *) vm_map(nullptr, 0);
	auto *page2 = (char *) vm_map(nullptr, 0);

	auto *filename0 = page0 + VM_PAGESIZE - 5;
	auto *filename1 = page1 + VM_PAGESIZE - 2;
	// auto *filename2 = page2 + VM_PAGESIZE - 3;
	std::strcpy(filename0, "data1.bin");
	std::strcpy(filename1, "data2.bin");
	// std::strcpy(filename2, "data3.bin");

	auto *file_page0 = (char *) vm_map(filename0, 0);
	auto *file_page1 = (char *) vm_map(filename1, 1);
	// auto *file_page2 = (char *) vm_map(filename2, 0);

	std::strcpy(file_page0, "this is data1.bin\n");
	std::strcpy(file_page1, "this is data2.bin\n");
	// std::strcpy(file_page2, "this is data3.bin\n");

	auto *page3 = (char *) vm_map(nullptr, 0);

	std::strcpy(page3, "test1\n");

	for (unsigned int i=0; i<1930; i++) {
		cout << page3[i];
	}

	cout << "contents of data1.bin: " << file_page0;
	cout << "contents of data2.bin: " << file_page1;
	// cout << "contents of data3.bin: " << file_page2;

	cout << "contents of swap-backed page3: " << page3;

	return 0;
}
