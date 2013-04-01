cmake_minimum_required (VERSION 2.8.9)

project (signal)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3")

add_executable (signal main.cpp)
