cmake_minimum_required(VERSION 2.8.9)

include (cotire)

project (coroutine)

include_directories (include ..)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall")

add_library (coroutine STATIC src/coroutine.cpp)

cotire (coroutine)
