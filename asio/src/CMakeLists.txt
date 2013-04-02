cmake_minimum_required (VERSION 2.8.9)

project (asio-example)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -O2")
add_definitions (-D__USE_W32_SOCKETS -DBOOST_ASIO_DISABLE_IOCP)

add_executable (asio-example main.cpp)
