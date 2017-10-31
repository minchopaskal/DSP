#include <iostream>

#include "BTree/BTree.h"
#include "List/List.h"
#include "PriorityQueue/PriorityQueue.h"


void endl() {
    std::cout << std::endl;
    return;
}

struct StringComparison {
   bool operator() (std::string fstString,
                    std::string sndString) const
   {
       return fstString.compare(sndString) <= 0;
   }
};

void priorityQueueTest() {
    PriorityQueue<char, std::string, StringComparison>
            myQueue;

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
    BTree<> bTree(10);
    bTree.insertOrdered(5);
    bTree.insertOrdered(20);
    bTree.insertOrdered(15);
    bTree.insertOrdered(25);

    std::cout << "Ordered tree: " << bTree; endl();

    std::cout<< "Count of nodes in tree: "
             << bTree.count(); endl();
    std::cout<< "Count of evens in tree: "
             << bTree.countEvens(); endl();

    std::cout<< "Count of odds in tree: " <<
    bTree.searchCount([](const int& data) {
                          return data % 2 == 1;
                      }); endl();

    std::cout<< "Height of tree: "
             << bTree.height(); endl();

    std::cout<< "Count of leaves of tree: "
             << bTree.countLeaves(); endl();

    std::cout << "Max Leaf: "
              << bTree.maxLeaf(); endl();

    BTree<>* t = new BTree<>();

    std::cout << "Max Leaf of empty tree: "
              << t->maxLeaf(); endl();

    delete t;

    std::cout << "Element at empty: "
              << bTree.getElement(""); endl();

    std::cout << "Element at RL: "
              << bTree.getElement("RL"); endl();

    std::cout << "Element at RLR: "
              << bTree.getElement("RLR"); endl();

}

int main() {
//    priorityQueueTest();
//    endl();
//    listSortTest();

    bTreeTest();

    return 0;
}