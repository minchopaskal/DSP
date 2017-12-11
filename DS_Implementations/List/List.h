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
        node(const T& data, node* prev, node* next) {
            this->data = data;
            this->prev = prev;
            this->next = next;
        }
    };

    class Iterator {
    private:
      node* ptr;
    public:
      using I = Iterator;
      explicit Iterator(node* ptr = nullptr) : ptr(ptr)  {}
      I next() const {
        return I(ptr->next);
      }

      I prev() const { return I(ptr->prev); }

      T& get() const {
        return ptr->data;
      }

      T const& cget() const {
        return ptr->data;
      }

      bool valid() const {
        return ptr != nullptr;
      }

      bool operator==(I const& it) const {
        return ptr == it.ptr;
      }

      bool operator!=(I const& it) const {
        return !(*this == it);
      }

      T& operator*() {
        return get();
      }

      T operator++() {
        return *this = next();
      }

      I operator++(int) {
        I prev = *this;
        *this = ++(*this);
        return prev;
      }

      operator bool() const {
        return valid();
      }
    };
    
    node* head;
    node* tail;
    node* end_el;
    std::size_t size;

    void emptyList();

    node* mergeSort(node*);
    node* mergeLists(node*, node*);

public:
    using iterator = Iterator;
    using const_iterator = const Iterator;
    
    // Big four
    List(int cnt = 0, T data = T());
    List(const List&);
    List&operator=(const List&);
    ~List();

    // Itarators
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(end_el); }
    const iterator cbegin() const { return iterator(head); }
    const iterator cend() const { return iterator(end_el); }

    // Capacity
    bool empty() const { return size == 0; }
    std::size_t getSize() const { return size; }

    // Element access
    T front() const { return head->data; }
    T back() const { return tail->data; }

    // Modifiers
    void push_back(const T&);
    bool pop_back();
    void push_front(const T&);
    bool pop_front();

    // Operations
    void sort();
    void reverse();
    void print() const;
    
};

#include "List.cpp"


#endif //_LIST_H
