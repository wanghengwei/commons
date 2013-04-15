cmake_minimum_required (VERSION 2.8.9)

project (myproj)

set (CMAKE_CXX_FLAGS "-std=c++11")
set (CMAKE_INSTALL_PREFIX .)

include_directories (.)
link_directories (lib)

add_subdirectory (pqueue/src)

add_subdirectory (tests/src)
