#include <chrono> 
#include <iostream>
#include "rbtree.cpp"

using rbti = red_black_tree<int>;

int main() {
  rbti t;
  std::cout << sizeof(rbti::node) << std::endl;
  t.insert(5);
  t.insert(6);
  t.insert(2);
  t.insert(8);
  
  t.print();
}
