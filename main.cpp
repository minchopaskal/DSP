#include "PriorityQueue/PriorityQueue.h"

struct StringComparison {
   bool operator() (std::string fstString, std::string sndString) const {
       return fstString.compare(sndString) <= 0;
   }
};

int main() {
    PriorityQueue<char, std::string, StringComparison> myQueue;

    myQueue.push('a', "apple");
    myQueue.push('b', "bapple");
    myQueue.push('c', "syrup");
    myQueue.push('d', "maple");

    myQueue.print();
    return 0;
}