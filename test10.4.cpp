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
  std::cout << "test1 start\n";
  char* filename = static_cast<char *>(vm_map(nullptr, 0));
  char* filename1 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename2 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename3 = static_cast<char *>(vm_map(nullptr, 0));
  strcpy(filename, "lampson83.txt");
  strcpy(filename1, "data1.bin");
  strcpy(filename2, "data2.bin");
  strcpy(filename3, "data3.bin");

  char* p = static_cast<char *>(vm_map (filename, 0));
  for (int i = 0; i < 20; i++) {
    cout << filename[i];
  }
  for (int i = 0; i < 20; i++) {
    cout << filename1[i];
  }
  for (int i = 0; i < 20; i++) {
    cout << filename2[i];
  }
  for (int i = 0; i < 20; i++) {
    cout << filename3[i];
  }
  for (int i = 0; i < 20; i++) {
    cout << filename2[i];
  }
  for (int i = 0; i < 20; i++) {
    cout << filename2[i];
  }
}