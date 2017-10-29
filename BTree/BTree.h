//
// Created by ellie on 28.10.17.
//

#ifndef _BTREE_H
#define _BTREE_H

#include <ostream>

template <class T = int, class Compare = std::less<int>>
class BTree {
private:
    struct node {
        T data;
        node* left;
        node* right;

        node(T data = T(), node* left = nullptr, node* right = nullptr) :
                data(data), left(left), right(right) {}
    };

    node* root;

private:
    node* copy(node*&, const node*);
    void erase(node*&);

    void insert(const T&, node*&);

    void print(const node*) const;
public:
    BTree();
    BTree(const BTree&);
    BTree&operator=(BTree);
    ~BTree();

    bool empty() const { return root == nullptr; }
    void insert(const T&);
    void print() const { print(root); };

    // Implementing the copy-and-swap idiom
    friend void swap(BTree<T, Compare>&, BTree<T, Compare>&);
};

#include "BTree.cpp"

#endif //_BTREE_H
