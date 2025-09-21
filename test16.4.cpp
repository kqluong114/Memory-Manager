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

  strcpy(filename0, "lampson83.txt");
  strcpy(filename1, "lampson83.txt");
  strcpy(filename2, "lampson83.txt");
  strcpy(filename3, "lampson83.txt");

  
}