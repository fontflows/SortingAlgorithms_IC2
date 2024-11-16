cmake_minimum_required(VERSION 3.29)
project(SortingAlgorithms)

set(CMAKE_CXX_STANDARD 20)

add_executable(SortingAlgorithms main.cpp
        sorting.cpp
        sorting.h
        utils.cpp
        utils.h
)
