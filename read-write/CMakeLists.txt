include (cotire)

project (read-write)

set (CMAKE_C_COMPILER "clang")
set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_CXX_FLAGS "-std=c++11")

add_executable (read-write src/main.cpp)
