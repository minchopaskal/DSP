cmake_minimum_required(VERSION 3.8)
project(SDP_seminar)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        BTree/BTree.cpp
        BTree/BTree.h
        List/List.cpp
        List/List.h
        PriorityQueue/PriorityQueue.cpp
        PriorityQueue/PriorityQueue.h
        Stack/Stack.cpp
        Stack/Stack.h
        main.cpp)

add_executable(SDP_seminar ${SOURCE_FILES})