cmake_minimum_required (VERSION 2.8.9)

project (asio-example)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -O2")
add_definitions (-D__USE_W32_SOCKETS)

add_executable (asio-example main.cpp)
