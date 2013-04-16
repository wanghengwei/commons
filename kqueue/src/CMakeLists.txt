cmake_minimum_required (VERSION 2.8.10)

project (kqueue)

#set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

add_library (kqueue kqueue.cpp)
#add_executable (kqueue kqueue.cpp)
