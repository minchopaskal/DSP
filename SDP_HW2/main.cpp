#include <ctime>
#include <iostream>
#include "src/browser/browser.h"

void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

int main() {
  std::cout << "OK!\n";
  Browser chrome;
  
  chrome.print();
  std::cout << std::endl;
  wait(2);
  chrome.insert("www.google.com");
  std::cout << std::endl;
  chrome.print();
  chrome.back();
  wait(2);
  chrome.go("www.facebook.com");
  std::cout << std::endl;
  chrome.print();
  chrome.sort(true);
  std::cout << std::endl;
  chrome.print();
  std::cout << std::endl;
  chrome.sort(false);
  chrome.print();
  
  return 0;
}
