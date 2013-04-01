cmake_minimum_required (VERSION 2.8.9)

project (profiler)

include_directories (../../)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -O2")
set (CMAKE_INSTALL_PREFIX "../../")

add_library (profiler duration_counter.cpp)

install (TARGETS profiler DESTINATION lib/)
