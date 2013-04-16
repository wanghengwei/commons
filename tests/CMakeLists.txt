cmake_minimum_required (VERSION 2.8.9)

project (tests)

add_executable (tests test-kqueue.cpp)

target_link_libraries (tests kqueue)
