#include <iostream>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main() {
	pid_t x = fork();
		std::cout << 1 << std::endl;
		char* filename = static_cast<char *>(vm_map(nullptr, 0));
		char* filename1 = static_cast<char *>(vm_map(nullptr, 1));
		std::cout << 1.5 << std::endl;
		std::strcpy(filename, "data4.bin");
		std::strcpy(filename1, "data4.bin");
	if (x){
		if (fork()){
			std::cout << 2 << std::endl;
			char* page1 = static_cast<char *>(vm_map(filename, 0));
			page1[0] = 'b';
		}
		else {
			char* page1 = static_cast<char *>(vm_map(filename, 0));
			std::cout << 3 << std::endl;
			char* page2 = static_cast<char *>(vm_map(filename1, 1));
			std::cout << 4 << std::endl;
			char* page3 = static_cast<char *>(vm_map(filename1, 1));
			std::cout << 5 << std::endl;
			filename[0] = 'a';
			std::cout << 6 << std::endl;
			page1[0] = 'b';
			std::cout << 7 << std::endl;
			page2[0] = 'c';
			std::cout << 8 << std::endl;
			page3[0] = 'd';
			std::cout << 9 << std::endl;
			cout << filename[0] << std::endl;
			std::cout << 10 << std::endl;
			cout << page1[0] << std::endl;
			std::cout << 11 << std::endl;
			cout << page2[0] << std::endl;
			std::cout << 12 << std::endl;
			cout << page3[0] << std::endl;
			std::cout << 13 << std::endl;
			pid_t y = fork();
			pid_t a = fork();
			exit(0);
		}
	}
	pid_t z = fork();
	pid_t q = fork();
	std::cout << 14 << std::endl;
	char* page4 = static_cast<char *>(vm_map(nullptr, 0));
	std::cout << 15 << std::endl;
	char* page5 = static_cast<char *>(vm_map(filename, 0));
	std::cout << 16 << std::endl;
	char* page6 = static_cast<char *>(vm_map(filename, 1));
	vm_yield();
	std::cout << 17 << std::endl;
	char* page7 = static_cast<char *>(vm_map(filename, 1));
	std::cout << 18 << std::endl;
	char* page8 = static_cast<char *>(vm_map(filename, 2));
	std::cout << 19 << std::endl;
	for (int i = 0; i < 10; ++i){
		pid_t q = fork();
		if (fork()) {
			fork();
			vm_yield();
			if (fork()){
				fork();
				for (int i = 0; i < 10; ++i){
					fork();
					vm_yield();
				}
			}
		}
		exit(q);
		fork();
		vm_yield();
		fork();
		for (int i = 0; i < 10; ++i){
		pid_t q = fork();
		if (fork()) {
			fork();
			vm_yield();
			if (fork()){
				fork();
				for (int i = 0; i < 10; ++i){
					fork();
					vm_yield();
				}
			}
		}
		exit(q);
		fork();
		vm_yield();
		fork();
	}
	}
	page4[0] = 'e';
	std::cout << 20 << std::endl;
	page5[0] = 'f';
	std::cout << 21 << std::endl;
	page7[0] = 'g';
	std::cout << 22 << std::endl;
	cout << page4[0] << std::endl;
	std::cout << 23 << std::endl;
	cout << page5[0] << std::endl;
	std::cout << 24 << std::endl;
	cout << page6[0] << std::endl;
	std::cout << 25 << std::endl;
	cout << page7[0] << std::endl;
	std::cout << 26 << std::endl;
	cout << page8[0] << std::endl;
	std::cout << 27 << std::endl;
	return 0;
}