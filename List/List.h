//
// Created by ellie on 17.10.17.
//

#ifndef _LIST_H
#define _LIST_H

#include <cstddef>

template <typename T>
class List {
private:
    struct node {
        T data;
        node* prev;
        node* next;
        node(T data, node* prev, node* next) {
            this->data = data;
            this->prev = prev;
            this->next = next;
        }
    };

    node* head;
    node* tail;
    std::size_t size;

    void emptyList();

    node* mergeSort(node*);
    node* mergeLists(node*, node*);

public:
    // Big four
    List(int cnt = 0, T data = T());
    List(const List&);
    List&operator=(const List&);
    ~List();

    // Capacity
    bool empty() const { return head == nullptr; }
    std::size_t getSize() const { return size; }

    // Element access
    T front() const { return head->data; }
    T back() const { return tail->data; }

    // Modifiers
    void push_back(T);
    void pop_back();
    void push_front(T);
    void pop_front();

    // Operations
    void sort();
    void reverse();
    void print() const;
};

#include "List.cpp"


#endif //_LIST_H
