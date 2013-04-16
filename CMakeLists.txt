cmake_minimum_required (VERSION 2.8.9)

project (myproj)

set (CMAKE_CXX_FLAGS "-std=c++11")

#For OSX & iOS, using libc++ instead of libstdc++
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")

set (CMAKE_INSTALL_PREFIX .)

include_directories (.)
link_directories (lib)

add_subdirectory (pqueue/src)

add_subdirectory (tests/src)

add_subdirectory (kqueue/src)
