// Test changing files-backed pages
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main() {
  char* filename0 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename1 = static_cast<char *>(vm_map(nullptr, 0));


  strcpy(filename0, "lampson83.txt");
  strcpy(filename1, "data1.bin");


  char* filename00 = static_cast<char *>(vm_map(filename0, 0));
  char* filename01 = static_cast<char *>(vm_map(filename0, 0));
  char* filename02 = static_cast<char *>(vm_map(filename0, 0));
  char* filename03 = static_cast<char *>(vm_map(filename0, 0));

  char* filename10 = static_cast<char *>(vm_map(filename1, 0));
  char* filename11 = static_cast<char *>(vm_map(filename1, 0));
  char* filename12 = static_cast<char *>(vm_map(filename1, 0));
  char* filename13 = static_cast<char *>(vm_map(filename1, 0));


  // strcpy(filename0, "data2.bin");
  // strcpy(filename1, "data3.bin");


	std::cout << "first prints\n";
	cout << filename03[0] << std::endl;
	cout << filename13[0] << std::endl;
	cout << filename10[0] << std::endl;
	cout << filename01[0] << std::endl;
	cout << filename00[0] << std::endl;
	cout << filename10[0] << std::endl;
	cout << filename00[0] << std::endl;
	cout << filename12[0] << std::endl;
	cout << filename12[0] << std::endl;
	cout << filename13[0] << std::endl;


	filename00[0] = 'a';
	filename11[0] = 'b';
	filename01[0] = 'c';
	filename13[0] = 'd';
	cout << "lol1 " << filename00[0] << std::endl;
	cout << "lol2 " << filename12[0] << std::endl;
	filename11[0] = 'e';
	filename01[0] = 'f';
	cout << "lol3 " << filename00[0] << std::endl;
	cout << "lol4 " << filename12[0] << std::endl;
	filename11[0] = 'g';
	filename01[0] = 'h';
	filename0[0] = 'i';
	filename12[0] = 'j';
	filename02[0] = 'k';
	filename13[0] = 'l';

	std::cout << "second prints\n";
	cout << filename10[0] << std::endl;
	cout << filename10[0] << std::endl;
	cout << filename01[0] << std::endl;
	cout << filename12[0] << std::endl;
	cout << filename00[0] << std::endl;
	cout << filename13[0] << std::endl;
	cout << filename03[0] << std::endl;
	cout << filename00[0] << std::endl;
	cout << filename13[0] << std::endl;
	cout << filename12[0] << std::endl;


}