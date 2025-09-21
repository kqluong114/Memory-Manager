// Swap file eviction
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"
#include <vector>

using std::cout;
using std::endl;

int main()
{
	fork();
  std::cout << "test1 start\n";
  char* filename0 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename1 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename2 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename3 = static_cast<char *>(vm_map(nullptr, 0));
  strcpy(filename0, "lampson83.txt");
  strcpy(filename1, "data1.bin");
  strcpy(filename2, "data2.bin");
  strcpy(filename3, "data3.bin");
	vm_yield();
  char* filename4 = static_cast<char *>(vm_map(filename0, 0));
  char* filename5 = static_cast<char *>(vm_map(filename0, 0));
  char* filename6 = static_cast<char *>(vm_map(filename1, 0));
  char* filename7 = static_cast<char *>(vm_map(filename1, 0));
  char* filename8 = static_cast<char *>(vm_map(filename2, 0));
  char* filename9 = static_cast<char *>(vm_map(filename3, 0));
	vm_yield();
  char* p = static_cast<char *>(vm_map (filename0, 0));
  for (int i = 0; i < 20; i++) {
    cout << filename0[i];
  }
  cout << std::endl;
  for (int i = 0; i < 20; i++) {
    cout << filename1[i];
  }
  cout << std::endl;
  for (int i = 0; i < 20; i++) {
    cout << filename2[i];
  }
  cout << std::endl;
  for (int i = 0; i < 20; i++) {
    cout << filename3[i];
  }
  cout << std::endl;
  for (int i = 0; i < 20; i++) {
    cout << filename4[i];
  }
  cout << std::endl;
  for (int i = 0; i < 20; i++) {
    cout << filename5[i];
  }
  cout << std::endl;
  for (int i = 0; i < 20; i++) {
    cout << filename6[i];
  }
  cout << std::endl;
  for (int i = 0; i < 20; i++) {
    cout << filename7[i];
  }
  cout << std::endl;
}