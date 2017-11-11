//
// Created by ellie on 11/11/17.
//

#include <cmath>
#include <iostream>
#include <fstream>
#include "Labyrinth.h"


Labyrinth::Labyrinth(const std::string &name) {
    read(name);
    findStartEnd();
}

Labyrinth::~Labyrinth() {
    for(uint i = 0; i < size; ++i) {
        delete map[i];
    }
    delete map;
}

bool Labyrinth::findPathRec(position curr) {
    // bottom of recursion
    print();

    if(curr == end) {
        return true;
    }

    // Else check every neighbour field
    // Enter if it's passable
    for(int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if(abs(i + j) != 1)
                continue;

            position next{curr.first + i, curr.second + j};
            if (isPassable(next)) {
                map[curr.first][curr.second] = '.';
                map[next.first][next.second] = 'm';
                if(findPathRec(next)) return true;
                map[curr.first][curr.second] = 'm';
                map[next.first][next.second] = '0';
            }
        }
    }

    // So there is no path after all
    return false;
}

bool Labyrinth::findPath() {
    StackPositions stack;
    StackFrame stackFrame;

    // Start position
    stack.push(start);
    stackFrame.push(stack);

    // For every position in stackFrame.top()
    // we get a set of the new positions and
    // "recurse"
    while(!stackFrame.empty()) {
        StackPositions& currPositions = stackFrame.top();

        position& curr = currPositions.top();
        char& currPos = map[curr.first][curr.second];


        currPos = 'm';
        print();

        if(curr == end) {
            return true;
        }

        // Get stack of new positions
        StackPositions newPositions;
        for(int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if(abs(i + j) != 1)
                    continue;
                position next{curr.first + i, curr.second + j};
                if (isPassable(next)) {
                    newPositions.push(next);
                }
            }
        }

        // If there are no new positions
        // we move back(remove the current one)
        if(newPositions.empty()) {
            currPos = '0';
            currPositions.pop();

            // if no positions are left from the stack
            // we remove this set from the stackFrame
            if(currPositions.empty()) {
                stackFrame.pop();

                // So the prev position wasn't
                // we remove it
                stackFrame.top().pop();
            }

            // We move to the next possible
            // position
            position& next = stackFrame.top().top();
        } else {
            // Else there are new positions to try
            stackFrame.push(newPositions);
            // We will "recurse" on them later
            // but let's get out of curr position!
            currPos = '.';
        }
    }

    return false;
}

bool Labyrinth::isPassable(position next) const {
    return 0 <= next.first < size &&
           0 <= next.second < size &&
           map[next.first][next.second] != '1' &&
           map[next.first][next.second] != '.';
}

void Labyrinth::findStartEnd() {
    for(uint i = 0; i < size; ++i) {
        for (uint j = 0; j < size; ++j) {
            char curr = map[i][j];
            if(curr == 'm') {
                start.first = i;
                start.second = j;
            }
            if(curr == 'e') {
                end.first = i;
                end.second = j;
            }
        }
    }
}

void Labyrinth::read(const std::string &name) {
    std::string path = "../data/" + name;
    std::ifstream file(path);

    if(!file.is_open()) {
        std::cout << "Corrupted file!\n";
        return;
    }

    file >> size;
    file.get();

    map = new char*[size];
    for(uint i = 0; i < size; ++i) {
        map[i] = new char[size];
    }


    std::string line;
    int row = 0;
    while(std::getline(file, line)) {
        int column = 0;
        for(int i = 0; i < line.length(); i += 2) {
            map[row][column] = line[i];
            ++column;
        }
        ++row;
    }
}

void Labyrinth::printPath() {
    if(findPath()) {
        std::cout << "Oh yea\n";
        return;
    }
    std::cout << "No path!\n";
}

void Labyrinth::print() const {
    for(uint i = 0; i < size; ++i) {
        for(uint j = 0; j < size; ++j) {
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}