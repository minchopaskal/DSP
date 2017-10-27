//
// Created by ellie on 23.10.17.
//

#ifndef SDP_SEMINAR_PRIORITYQUEUE_H
#define SDP_SEMINAR_PRIORITYQUEUE_H

#include <zconf.h>

/** Priority Queue
 *  push() - O(n)
 *  pop() - O(1)
 */

template <class T = int, class S = int, class Compare = std::less<int>>
class PriorityQueue {
private:
    struct node {
        T data;
        S priority;
        node* next;
        node(T data, S priority = 0, node* next = nullptr) :
                data(data), priority(priority), next(next) { }
    };

    node* head;
    size_t size;
    Compare compareFunc;

    void copy(node*);
    void erase();

public:
    // Big Four
    PriorityQueue();
    PriorityQueue(const PriorityQueue&);
    PriorityQueue&operator=(const PriorityQueue&);
    ~PriorityQueue();

    // Capacity
    bool empty() const { return size == 0; }
    size_t getSize() const { return size; }

    // Element access
    T top() const { return head->data; }
    void print() const;

    // Modifiers
    void pop();
    void push(T, S);
};

#include "PriorityQueue.cpp"

#endif //SDP_SEMINAR_PRIORITYQUEUE_H
