#include <iostream>
#include <stack>
#include <sstream>
#include "Editor/Editor.h"
#include "Labyrinth/Labyrinth.h"

void lastMerge(std::stack<int>* merged, std::stack<int>& last) {
    while (!last.empty()) {
        int val = last.top();
        merged->push(val);
        last.pop();
    }
}

std::stack<int>& mergeStacks(std::stack<int>& leftStack, std::stack<int>& rightStack) {
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

void testMergeStacks() {
    std::stack<int> left;
    left.push(1);
    left.push(3);
    left.push(5);

    std::stack<int> right;
    right.push(1);
    right.push(2);
    right.push(6);

    std::stack<int> merged = mergeStacks(left, right);
    while(!merged.empty()) {
        std::cout << merged.top() << " ";
        merged.pop();
    }
}

void testEditor() {
    Editor editor("");
    editor.insert(0, "This is new text!");
    editor.insert(17, " Whole new sentence!");
    std::cout << editor.getText() << std::endl;
    editor.undo();
    std::cout << editor.getText() << std::endl;
    editor.redo();
    std::cout << editor.getText() << std::endl;
    editor.redo();
    editor.undo();
    std::cout << editor.getText() << std::endl;
}

int getCount(std::string::iterator& it) {
    std::string currCountStr = "";
    while(*it != '(') {
        currCountStr += *it;
        ++it;
    }
    std::stringstream numStr(currCountStr);
    int currCount = 0;
    numStr >> currCount;
    return currCount;
}

std::string decompressString(std::string& str) {
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

void testLabyrinth() {
    Labyrinth labyrinth("lab.txt");
    labyrinth.printPath();
}


int main() {
    testMergeStacks();

    testEditor();

    std::string testString = "12(AB2(C))";
    std::cout << decompressString(testString) << std::endl;

    testLabyrinth();
}