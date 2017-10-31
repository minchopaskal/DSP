//
// Created by ellie on 28.10.17.
//

#ifndef _BTREE_CPP
#define _BTREE_CPP

#include <algorithm>
#include <cmath>
#include <iostream>

#include "BTree.h"

template <class T, class Compare>
void swap(BTree<T, Compare>& tree, BTree<T, Compare>& other) {
    using std::swap;
    std::swap(tree.root, other.root);
}

template <class T, class Compare>
BTree<T, Compare>::BTree() : root(nullptr) { }

template <class T, class Compare>
BTree<T, Compare>::BTree(const T& data,
                         const BTree<T, Compare>& lt,
                         const BTree<T, Compare>& rt) {

    root = new BTree<T,Compare>::node(data, copy(lt.root), copy(rt.root));
}

template <class T, class Compare>
BTree<T, Compare>::BTree(const BTree& other) : root(nullptr) {
    root = copy(other.root);
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
BTree<T, Compare>::copy(const node* root) {
    if(root == nullptr)
        return nullptr;

    return new node(root->data,
                    copy(root->right),
                    copy(root->left));
}

template <class T, class Compare>
void BTree<T, Compare>::erase(node*& root) {
    if(!root)
        return;

    erase(root->right);
    erase(root->left);
    delete root;
}

template <class T, class Compare>
void BTree<T, Compare>::insertOrdered(const T& data) {
    insertOrdered(data, root);
}

template <class T, class Compare>
void BTree<T, Compare>::insertOrdered(const T& data, node*& root) {
    if(empty()) {
        this->root = new node(data, nullptr, nullptr);
        return;
    }
    if(Compare()(data, root->data)) {
        if(!root->left) {
            root->left = new node(data, nullptr, nullptr);
            return;
        }
        insertOrdered(data, root->left);
    } else {
        if(!root->right) {
            root->right = new node(data, nullptr, nullptr);
            return;
        }
        insertOrdered(data, root->right);
    }
}

template <class T, class Compare>
std::ostream& BTree<T, Compare>::print(const node* root, std::ostream& os) const {
    if(!root)
        return os;

    os << "(";
    print(root->left, os);
    os << ") ";
    os << root->data;
    os << " (";
    print(root->right, os);
    os << ")";
    return os;
}

template <class T, class Compare>
std::ostream& operator<<(std::ostream& os, const BTree<T,Compare>& tree) {
    return tree.print(tree.root, os);
};

/*
 * Functions from exercise
 */
template <class T, class Compare>
int BTree<T, Compare>::count() const {
    searchCount([](const T& data) {
                    return true;
                }, root);
};


template <class T, class Compare>
int BTree<T, Compare>::countEvens() const {
    searchCount([](const T& data) {
                    return data % 2 == 0;
                }, root);
};


template <class T, class Compare>
int BTree<T, Compare>::searchCount(bool (*pred)(const T &)) const {
    searchCount(pred, root);
}

template <class T, class Compare>
int BTree<T, Compare>::searchCount(bool (*pred)(const T &), const node* root) const {
    if(root == nullptr) {
        return 0;
    }

    return (pred(root->data) ? 1 : 0) +
           searchCount(pred, root->right) +
           searchCount(pred, root->left);
}

template <class T, class Compare>
int BTree<T, Compare>::height() const {
    return height(root);
}

template <class T, class Compare>
int BTree<T, Compare>::height(const node* root) const {
    if(root == nullptr) {
        return 0;
    }

    return 1 + std::max(height(root->right), height(root->left));
}

template <class T, class Compare>
int BTree<T, Compare>::countLeaves() const {
    countLeaves(root);
}

template <class T, class Compare>
int BTree<T, Compare>::countLeaves(const node* curr) const {
    if (curr == nullptr) {
        return 0;
    }

    if (curr->left == nullptr && curr->right == nullptr) {
        return 1;
    }

    return countLeaves(curr->left) + countLeaves(curr->right);
}

template <class T, class Compare>
const T& BTree<T, Compare>::maxLeaf() const {
    const node* leaf = maxLeaf(root);
    if(leaf) {
        return leaf->data;
    }
    return *(new T());
};

template <class T, class Compare>
const typename BTree<T,Compare>::node*
BTree<T, Compare>::maxLeaf(const node* curr) const {
    if(curr == nullptr)
        return nullptr;

    if(curr->left == nullptr && curr->right == nullptr) {
        return curr;
    }

    const node* lData = maxLeaf(curr->left);
    const node* rData = maxLeaf(curr->right);

    if(lData == nullptr)
        return rData;
    if(rData == nullptr)
        return lData;

    return Compare()(lData->data, rData->data) ? rData : lData;
};

template <class T, class Compare>
const T& BTree<T, Compare>::getElement(const char* s) const {
    const node* element = getElement(s, root);
    if(element != nullptr) {
        return element->data;
    }
    return *(new T());
};

template <class T, class Compare>
const typename BTree<T,Compare>::node*
BTree<T, Compare>::getElement(const char* s, const node* curr) const {
    if(curr == nullptr) {
        return nullptr;
    }
    if(*s == '\0') {
        return curr;
    }

    return getElement(++s, getNodeBySymbol(*s, curr));
};

template <class T, class Compare>
const typename BTree<T,Compare>::node*
BTree<T, Compare>::getNodeBySymbol(char symbol, const node* root) const {
    switch(symbol) {
        case 'L':
            return root->left;
        case 'R':
            return root->right;
        default:
            return nullptr;
    }
}

#endif //_BTREE_CPP