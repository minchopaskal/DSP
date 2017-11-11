cmake_minimum_required(VERSION 3.8)
project(SDP_Homework)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Editor/Editor.cpp Editor/Editor.h Labyrinth/Labyrinth.cpp Labyrinth/Labyrinth.h)
add_executable(SDP_Homework ${SOURCE_FILES})