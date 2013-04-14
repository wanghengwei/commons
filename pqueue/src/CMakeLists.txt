cmake_minimum_required (VERSION 2.8.9)

project (pqueue)

set (CMAKE_CXX_FLAGS "-std=c++11")

add_library (pqueue pqueue.cpp)
