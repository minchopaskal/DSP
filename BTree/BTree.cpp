//
// Created by ellie on 28.10.17.
//

#ifndef _BTREE_CPP
#define _BTREE_CPP

#include <algorithm>
#include <iostream>
#include "BTree.h"

template <class T, class Compare>
void swap(BTree<T, Compare>& tree, BTree<T, Compare>& other) {
    using std::swap;
    std::swap(tree.root, other.root);
}

template <class T, class Compare>
BTree<T, Compare>::BTree() : root(nullptr) {}

template <class T, class Compare>
BTree<T, Compare>::BTree(const BTree& other) : root(nullptr) {
    copy(root, other.root);
}

template <class T, class Compare>
BTree<T, Compare>& BTree<T, Compare>::operator=(BTree rhs) {
    swap(*this, rhs);
    return *this;
}

template <class T, class Compare>
BTree<T, Compare>::~BTree() {
    erase(root);
}

template <class T, class Compare>
typename BTree<T, Compare>::node*
BTree<T, Compare>::copy(node*& curr, const node* root) {
    if(!root)
        return nullptr;

    if(!root->left && root->right)
        return new node(root->data, nullptr, nullptr);

    curr->right = copy(curr->right, root->right);
    curr->left = copy(curr->left, root->left);
}

template <class T, class Compare>
void BTree<T, Compare>::erase(node*& root) {
    if(!root || !root->right && !root->left) {
        delete root;
        return;
    }
    erase(root->right);
    erase(root->left);
    delete root;
}

template <class T, class Compare>
void BTree<T, Compare>::insert(const T& data) {
    insert(data, root);
}

template <class T, class Compare>
void BTree<T, Compare>::insert(const T& data, node*& root) {
    if(empty()) {
        this->root = new node(data, nullptr, nullptr);
        return;
    }
    if(Compare()(data, root->data)) {
        if(!root->left) {
            root->left = new node(data, nullptr, nullptr);
            return;
        }
        insert(data, root->left);
    } else {
        if(!root->right) {
            root->right = new node(data, nullptr, nullptr);
            return;
        }
        insert(data, root->right);
    }
}

template <class T, class Compare>
void BTree<T, Compare>::print(const node* root) const {
    if(!root)
        return;

    print(root->left);
    std::cout << root->data << " ";
    print(root->right);
}

#endif //_BTREE_CPP