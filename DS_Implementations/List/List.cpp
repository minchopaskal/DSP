//
// Created by ellie on 17.10.17.
//
#ifndef _LIST_CPP
#define _LIST_CPP

#include <iostream>
#include <iomanip>
#include "List.h"

template <typename T>
List<T>::List(int cnt, T data) :
        head(nullptr), tail(nullptr), size(0) {
    if(cnt != 0) {
        for(int i = 0; i < cnt; ++i) {
            push_back(data);
        }
    }
}

template <typename T>
List<T>::List(const List& other) : head(nullptr), tail(nullptr), size(0) {
    *this = other;
}

template <typename T>
List<T>& List<T>::operator=(const List& rhs) {
    if(this != &rhs) {
        emptyList();
        node* iter = rhs.head;
        while(iter){
            push_back(iter->data);
            iter = iter->next;
        }
    }
    return *this;
}

template <typename T>
void List<T>::emptyList() {
    while(!empty())
        pop_front();
}

template <typename T>
List<T>::~List() {
    emptyList();
}

template <typename T>
void List<T>::push_back(T data) {
    if(empty()) {
        head = new node(data, nullptr, nullptr);
        tail = head;
    } else {
        node* tmp = new node(data, tail, nullptr);
        tail->next = tmp;
        tail = tmp;
    }
    ++size;
}

template <typename T>
bool List<T>::pop_back() {
    if(empty())
        return false;
    node* tmp = tail;
    if(tail)
        tail = tail->prev;
    if(tail)
        tail->next = nullptr;
    delete tmp;
    --size;
    if(size <= 1) head = tail;
    return true;
}

template <typename T>
void List<T>::push_front(T data) {
    if(empty()){
        head = new node(data, nullptr, nullptr);
        tail = head;
    } else{
        node* tmp = new node(data, nullptr, head);
        head->prev = tmp;
        head = tmp;
    }
    ++size;
}

template <typename T>
bool List<T>::pop_front() {
    if(empty())
        return false;
    node* tmp = head;
    head = head->next;
    if(head)
        head->prev = nullptr;
    T tmpData = tmp->data;
    delete tmp;
    --size;
    if(size <= 1) tail = head;
    return true;
}

template <typename T>
void List<T>::sort() {
    head = mergeSort(head);
}

template <typename T>
typename List<T>::node* List<T>::mergeSort(node* lst) {
    if(lst->next == nullptr)
        return lst;
    node* slow;
    node* fast;

    slow = fast = lst;

    // Slicing list in two halves.
    while(fast) {
        slow = slow->next;
        fast = fast->next;
        if(fast)
            fast = fast->next;
    }

    node* sndHalf = slow;
    (slow->prev)->next = nullptr;
    slow->prev = nullptr;

    // Recursively sort each one of the halves.
    node* lst1 = mergeSort(lst);
    node* lst2 = mergeSort(sndHalf);
    
    // Merging the already sorted halves.
    return mergeLists(lst1, lst2);
}

template <typename T>
typename List<T>::node* List<T>::mergeLists(node* lst1, node* lst2) {
    // Iterators
    node* h1 = lst1;
    node* h2 = lst2;

    node* newHead;
    node* curr = h1->data < h2->data ? h1 : h2;

    newHead = curr;

    // After getting the smallest element
    // advance the coresponding iterator forward.
    if(h1->data < h2->data) {
        h1 = h1->next;
        if(h1)
            h1->prev = nullptr;
    } else {
        h2 = h2->next;
        if(h2)
            h2->prev = nullptr;
    }

    curr->next = nullptr;

    // Do the above thing in a loop
    while(h1 && h2) {
        if(h1->data <= h2->data) {
            curr->next = h1;
            h1 = h1->next;
        } else {
            curr->next = h2;
            h2 = h2->next;
        }
        curr->next->prev = curr;
        curr = curr->next;
    }

    // At the end one of the lists is null (or both)
    // We concatenate the full list at the end of the already
    // made one.
    if(!h1) {
        curr->next = h2;
        if(h2)
            h2->prev = curr;
    }
    if(!h2) {
        curr->next = h1;
        if(h1)
            h1->prev = curr;
    }

    return newHead;
}

template <typename T>
void List<T>::reverse() {
    node* tmp = head;
    head = tail;
    tail = tmp;

}

template <typename T>
void List<T>::print() const {
    node* iter = head;
    while(iter) {
        std::cout << iter->data << " ";
        iter = iter->next;
    }
    std::cout << std::endl;
}

#endif // _LIST_CPP
