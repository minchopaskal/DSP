#include <queue>
#include <sstream>

#include "StackAndQueueFunctions.h"

/*
 * Stack Functions
 */
void StackFunctions::lastMerge(std::stack<int> *merged, std::stack<int> &last) {
    while (!last.empty()) {
        int val = last.top();
        merged->push(val);
        last.pop();
    }
}

std::stack<int>& StackFunctions::mergeStacks(std::stack<int>& leftStack, std::stack<int>& rightStack) {
    std::stack<int>* merged = new std::stack<int>();
    while(!leftStack.empty() && !rightStack.empty()) {
        int lTop = leftStack.top();
        int rTop = rightStack.top();
        if(lTop > rTop) {
            leftStack.pop();
            merged->push(lTop);
        } else {
            rightStack.pop();
            merged->push(rTop);
        }
    }

    if(leftStack.empty()) {
        lastMerge(merged, rightStack);
    }
    if(rightStack.empty()) {
        lastMerge(merged, leftStack);
    }

    return *merged;
}

int StackFunctions::getCount(std::string::iterator& it) {
    std::string currCountStr;
    while(*it != '(') {
        currCountStr += *it;
        ++it;
    }
    std::stringstream numStr(currCountStr);
    int currCount = 0;
    numStr >> currCount;
    return currCount;
}

std::string StackFunctions::decompressString(std::string str) {
    std::stack<std::string> strings;
    strings.push("");
    std::stack<int> multipliers;

    for(std::string::iterator it = str.begin(); it != str.end();) {
        if(*it == ')') {
            ++it;
        }
        else if(isdigit(*it)) {
            int currCount = getCount(it);
            multipliers.push(currCount);
            strings.push("");
            ++it;
        } else {
            strings.top() += *it;
            ++it;
        }
    }

    while(!multipliers.empty()) {
        const std::string& curr = strings.top();
        strings.pop();
        int currCount = multipliers.top();
        multipliers.pop();

        while(currCount > 0) {
            strings.top() += curr;
            --currCount;
        }
    }
    return strings.top();
}

/*
 * Queue Functions
 */
void QueueFunctions::reverse(std::queue<int>& queue) {
    std::stack<int> container;
    while(!queue.empty()) {
        int curr = queue.front();
        container.push(curr);
        queue.pop();
    }
    while(!container.empty()) {
        int curr = container.top();
        queue.push(curr);
        container.pop();
    }
}

void QueueFunctions::printAscending(std::queue<int> unordered) {
    int sentinel;
    std::queue<int> ordered;
    while(!unordered.empty()) {
        unordered.push(sentinel);
        int currMin = unordered.front();
        unordered.pop();
        while(unordered.front() != sentinel) {
            int curr = unordered.front();
            if(curr < currMin) {
                unordered.push(currMin);
                unordered.pop();
                currMin = curr;
            } else {
                unordered.push(curr);
                unordered.pop();
            }
        }
        unordered.pop();
        ordered.push(currMin);
    }
    printQueue(ordered);
    std::cout << std::endl;
}

void QueueFunctions::printInterval(int* arr, int size, int a, int b) {
    if(b < a) {
        std::swap(a, b);
    }

    std::queue<int> less;
    std::queue<int> between;
    std::queue<int> greater;

    for(int i = 0; i < size; ++i) {
        int curr = arr[i];
        if(curr < a) {
            less.push(curr);
        }
        else if(curr <= b) {
            between.push(curr);
        } else {
            greater.push(curr);
        }
    }

    QueueFunctions::printQueue(less);
    QueueFunctions::printQueue(between);
    QueueFunctions::printQueue(greater);
}