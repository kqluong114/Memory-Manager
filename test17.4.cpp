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
  strcpy(filename1, "lampson83.txt");
  strcpy(filename2, "lampson83.txt");
  strcpy(filename3, "lampson83.txt");
  strcpy(filename4, "lampson83.txt");
  strcpy(filename5, "lampson83.txt");
  strcpy(filename6, "lampson83.txt");
  strcpy(filename7, "lampson83.txt");
  strcpy(filename0, "lampson83.txt");
  strcpy(filename1, "lampson83.txt");
  strcpy(filename2, "lampson83.txt");

	cout << filename3[0] << std::endl;
	cout << filename0[0] << std::endl;
	cout << filename3[0] << std::endl;
	cout << filename3[0] << std::endl;
	cout << filename5[2] << std::endl;
	cout << filename4[0] << std::endl;
	cout << filename6[2] << std::endl;
	cout << filename2[1] << std::endl;
	cout << filename3[0] << std::endl;
	cout << filename0[0] << std::endl;
	cout << filename3[0] << std::endl;
	cout << filename3[0] << std::endl;
	cout << filename5[2] << std::endl;
	cout << filename4[0] << std::endl;
	cout << filename6[2] << std::endl;
	cout << filename0[1] << std::endl;
	cout << filename1[1] << std::endl;
	cout << filename2[1] << std::endl;


	strcpy(filename0, "lampson83.txt");
  strcpy(filename1, "lampson83.txt");
  strcpy(filename2, "lampson83.txt");
  strcpy(filename3, "lampson83.txt");
  strcpy(filename4, "lampson83.txt");
  strcpy(filename5, "lampson83.txt");
  strcpy(filename6, "lampson83.txt");
  strcpy(filename7, "lampson83.txt");
  strcpy(filename0, "lampson83.txt");
  strcpy(filename1, "lampson83.txt");
  strcpy(filename2, "lampson83.txt");

  
}