include (cotire)
cmake_minimum_required(VERSION 2.8.4)
project (read-write)

#set (CMAKE_C_COMPILER "clang")
#set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_CXX_FLAGS "-std=c++11 -lpthread -Wall")

add_executable (read-write src/main.cpp)
cotire(read-write)
