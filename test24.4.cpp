// Test changing files-backed pages
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main() {
  char* filename0 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename1 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename2 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename3 = static_cast<char *>(vm_map(nullptr, 0));
	char* filename4 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename5 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename6 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename7 = static_cast<char *>(vm_map(nullptr, 0));

  strcpy(filename0, "lampson83.txt");
  // strcpy(filename0, "data2.bin");
	std::cout << "cout 01" << std::endl;
  strcpy(filename1, "lampson83.txt");
  // strcpy(filename1, "data2.bin");
	std::cout << "cout 02" << std::endl;
  strcpy(filename2, "lampson83.txt");
  // strcpy(filename2, "data2.bin");
	std::cout << "cout 03" << std::endl;
  strcpy(filename3, "lampson83.txt");
  // strcpy(filename3, "data2.bin");

	std::cout << "cout 1" << std::endl;
  char* filename8 = static_cast<char *>(vm_map(filename0, 0));
	std::cout << "cout 2" << std::endl;
  char* filename9 = static_cast<char *>(vm_map(filename0, 0));
	std::cout << "cout 3" << std::endl;
  char* filename10 = static_cast<char *>(vm_map(filename0, 0));
	std::cout << "cout 4" << std::endl;
  char* filename11 = static_cast<char *>(vm_map(filename9, 0));
	std::cout << "cout 5" << std::endl;
	char* filename12 = static_cast<char *>(vm_map(filename9, 0));
	std::cout << "cout 6" << std::endl;
  char* filename13 = static_cast<char *>(vm_map(filename1, 0));
	std::cout << "cout 7" << std::endl;
  char* filename14 = static_cast<char *>(vm_map(filename2, 0));
	std::cout << "cout 8" << std::endl;
  char* filename15 = static_cast<char *>(vm_map(filename3, 0));
	std::cout << "cout 9" << std::endl;
  char* filename16 = static_cast<char *>(vm_map(filename10, 0));
	std::cout << "cout 10" << std::endl;
  char* filename17 = static_cast<char *>(vm_map(filename10, 0));
	std::cout << "cout 11" << std::endl;


  strcpy(filename0, "data1.bin");
	std::cout << "cout 12" << std::endl;
  strcpy(filename1, "data1.bin");
	std::cout << "cout 13" << std::endl;
  strcpy(filename2, "data1.bin");
	std::cout << "cout 14" << std::endl;
  strcpy(filename3, "data1.bin");
	std::cout << "cout 15" << std::endl;
  // strcpy(filename9, "data1.bin");
	std::cout << "cout 16" << std::endl;
  strcpy(filename3, "data1.bin");
	std::cout << "cout 17" << std::endl;
  // strcpy(filename11, "data1.bin");
	std::cout << "cout 18" << std::endl;
  // strcpy(filename13, "data1.bin");
	std::cout << "cout 19" << std::endl;


	cout << filename3[0] << std::endl;
	std::cout << "line 1" << std::endl;
	cout << filename0[0] << std::endl;
	std::cout << "line 2" << std::endl;
	cout << filename3[0] << std::endl;
	std::cout << "line 3" << std::endl;
	cout << filename3[0] << std::endl;
	std::cout << "line 4" << std::endl;
	cout << filename5[2] << std::endl;
	std::cout << "line 5" << std::endl;
	cout << filename4[0] << std::endl;
	std::cout << "line 6" << std::endl;
	cout << filename6[2] << std::endl;
	std::cout << "line 7" << std::endl;
	cout << filename2[1] << std::endl;
	std::cout << "line 8" << std::endl;
	cout << filename10[1] << std::endl;
	std::cout << "line 9" << std::endl;
	cout << filename9[1] << std::endl;
	std::cout << "line 10" << std::endl;
	// cout << filename11[1] << std::endl;
	std::cout << "line 11" << std::endl;
	cout << filename13[1] << std::endl;
	std::cout << "line 12" << std::endl;
	cout << filename3[1] << std::endl;
	std::cout << "line 13" << std::endl;
	cout << filename2[1] << std::endl;
	std::cout << "line 14" << std::endl;
	cout << filename0[1] << std::endl;
	std::cout << "line 15" << std::endl;
	cout << filename1[1] << std::endl;
	std::cout << "line 16" << std::endl;
	cout << filename2[1] << std::endl;
	std::cout << "line 17" << std::endl;
	cout << filename15[1] << std::endl;
	std::cout << "line 18" << std::endl;
	// cout << filename16[0] << std::endl;
	std::cout << "line 19" << std::endl;
	// cout << filename17[0] << std::endl;
	std::cout << "line 20" << std::endl;
	cout << filename8[1] << std::endl;
	std::cout << "line 21" << std::endl;





	std::cout << "line 21" << std::endl;
	strcpy(filename0, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename1, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename2, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename3, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename4, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename5, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename6, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename7, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename0, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename1, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename2, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename0, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename1, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename2, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename3, "data1.bin");
	std::cout << "line 21" << std::endl;
  strcpy(filename9, "data1.bin");
	std::cout << "line 22" << std::endl;
  strcpy(filename3, "data1.bin");
	std::cout << "line 23" << std::endl;
  strcpy(filename1, "lampson83.txt");
	std::cout << "line 24" << std::endl;
  strcpy(filename13, "data1.bin");

	std::cout << "line 21" << std::endl;
  cout << filename13[1] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename3[1] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename2[1] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename0[1] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename1[1] << std::endl;
	std::cout << "line 30" << std::endl;
	cout << filename2[1] << std::endl;
	std::cout << "line 31" << std::endl;
	cout << filename15[1] << std::endl;
	std::cout << "line 32" << std::endl;
	cout << filename16[1] << std::endl;
	std::cout << "line 33" << std::endl;
	cout << filename17[1] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename8[1] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename3[0] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename0[0] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename3[0] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename3[0] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename5[2] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename4[0] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename6[2] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename15[1] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename16[1] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename17[1] << std::endl;
	std::cout << "line 21" << std::endl;
	cout << filename8[1] << std::endl;
	std::cout << "line 21" << std::endl;

}