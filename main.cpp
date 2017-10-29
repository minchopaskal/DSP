#include <iostream>

#include "BTree/BTree.h"
#include "List/List.h"
#include "PriorityQueue/PriorityQueue.h"


void newl() {
    std::cout << std::endl;
    return;
}

struct StringComparison {
   bool operator() (std::string fstString, std::string sndString) const {
       return fstString.compare(sndString) <= 0;
   }
};

void priorityQueueTest() {
    PriorityQueue<char, std::string, StringComparison> myQueue;

    myQueue.push('a', "apple");
    myQueue.push('b', "bapple");
    myQueue.push('c', "syrup");
    myQueue.push('d', "maple");

    myQueue.print();
}

void listSortTest() {
    List<int> list;
    list.push_back(13);
    list.push_back(110);
    list.push_back(17);
    list.push_back(8);
    list.push_back(23);
    list.push_back(1);
    list.push_back(45);
    list.push_back(32);
    list.push_back(5);

    list.print();
    list.sort();
    list.print();
}

void bTreeTest() {
    BTree<> bTree;
    bTree.insert(12);
    bTree.insert(5);
    bTree.insert(3);
    bTree.insert(6);
    bTree.insert(10);

    bTree.print();
}

int main() {
//    priorityQueueTest();
//    newl();
//    listSortTest();

    bTreeTest();

    return 0;
}