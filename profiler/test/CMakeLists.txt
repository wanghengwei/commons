cmake_minimum_required (VERSION 2.8.9)

project (profiler-test)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall")

add_definitions (-D_GLIBCXX_USE_NANOSLEEP)

include_directories (../../)
link_directories (../../lib/ /usr/local/lib/)

add_executable (profiler-test test_duration_counter.cpp)
target_link_libraries (profiler-test profiler)
