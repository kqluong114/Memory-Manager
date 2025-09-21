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
  char* filename6 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename5 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename7 = static_cast<char *>(vm_map(nullptr, 0));
  char* filename8 = static_cast<char *>(vm_map(nullptr, 0));

  strcpy(filename0, "lampson83.txt");

  char* lampson = static_cast<char *>(vm_map (filename0, 0));
  char* d1 = static_cast<char *>(vm_map (filename0, 0));
  char* d2 = static_cast<char *>(vm_map (filename0, 0));
  char* d3 = static_cast<char *>(vm_map (filename0, 0));
  char* d4 = static_cast<char *>(vm_map (filename0, 0));
  cout << "hi\n";
  for (unsigned int i=0; i<10; i++) {
    cout << lampson[i];
		
  }
  cout << "hi1\n";
	for (unsigned int i=0; i<10; i++) {
    cout << d1[0];
  }
  
}