cmake_minimum_required(VERSION 3.1)
project(project2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    AVLDict.cpp
    AVLDict.hpp
    BagOfPuzzleStates.hpp
    DoubleHashDict.cpp
    DoubleHashDict.hpp
    LinearHashDict.cpp
    LinearHashDict.hpp
    LinkedListDict.cpp
    LinkedListDict.hpp
    Makefile
    PredDict.hpp
    PuzzleState.hpp
    SliderPuzzle.cpp
    SliderPuzzle.hpp
    solve.cpp
    VectorPriorityQueue.cpp
    VectorPriorityQueue.hpp)

add_executable(project2 ${SOURCE_FILES})