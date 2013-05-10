cmake_minimum_required(VERSION 2.8)

project (fsm)

include_directories (~/Projects/boost-trunk)

set (CMAKE_CXX_FLAGS "-std=c++11 -g")

add_executable (fsm main.cpp)
