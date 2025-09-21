#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>
#include "vm_app.h"

using std::cout;

int main() {
	fork();
  std::cout << "test1 start\n";
  std::vector<char*> v;
  for (int i = 0; i < 2; ++i){
    char* filename = static_cast<char *>(vm_map(nullptr, 0));
    v.push_back(filename);
  }
	strcpy(v[0], "fampson83.txt");
	auto *page12 = static_cast<char *>(vm_map(v[0], 0));
}
