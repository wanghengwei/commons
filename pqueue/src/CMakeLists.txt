cmake_minimum_required (VERSION 2.8.9)

project (pqueue)

add_library (pqueue pqueue.cpp)

install (TARGETS pqueue ARCHIVE DESTINATION lib)
