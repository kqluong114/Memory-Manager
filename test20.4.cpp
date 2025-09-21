#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>
#include "vm_app.h"

using std::cout;

int main()
{
	fork();
  std::cout << "test1 start\n";
  std::vector<char*> v;
  for (int i = 0; i < 200; ++i){
    char* filename = static_cast<char *>(vm_map(nullptr, 0));
    v.push_back(filename);
  }
  for (int i = 0; i < 200; ++i){
    strcpy(v[i], "lampson83.txt");
  }


}
