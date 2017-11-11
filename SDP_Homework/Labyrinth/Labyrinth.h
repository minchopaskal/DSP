//
// Created by ellie on 11/11/17.
//

#ifndef SDP_HOMEWORK_LABYRINTH_H
#define SDP_HOMEWORK_LABYRINTH_H

#include <stack>
#include <string>

using position = std::pair<int, int>;

class Labyrinth {
private:
    using StackPositions = std::stack<position>;
    using StackFrame = std::stack<StackPositions>;

    char** map;
    uint size;
    position start;
    position end;

    bool findPathRec(position);
    bool findPath();

    bool isPassable(position) const;

    void findStartEnd();

public:
    Labyrinth(const std::string& name = "");
    Labyrinth(const Labyrinth&) = delete;
    Labyrinth&operator=(const Labyrinth&) = delete;
    ~Labyrinth();

    void read(const std::string&);
    void printPath();
    void print() const;
};


#endif //SDP_HOMEWORK_LABYRINTH_H
