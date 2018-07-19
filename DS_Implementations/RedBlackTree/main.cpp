#include <chrono> 
#include <iostream>

#include "rbtree.cpp"

using rbti = red_black_tree<int>;

int main() {
  rbti t;
  
  auto start = std::chrono::system_clock::now();
  for(int i = 0; i < 100000000; ++i) {
    t.insert(i);
  }
  auto end = std::chrono::system_clock::now();
  std::cout << ((std::chrono::duration<double>)(end - start)).count() << std::endl;

  //t.print();
}
