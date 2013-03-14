cmake_minimum_required(VERSION 2.8.9)

project (minizip)

#file (GLOB_RECURSE SRC_FILES src/*.c) 
set (SRC_FILES src/zip_package.cpp)
set (HEAD_FILES include/zip_package.h)

include_directories (include)

add_library (minizip STATIC ${SRC_FILES})

set (CMAKE_C_FLAGS "-DIOAPI_NO_64")
set (CMAKE_CXX_FLAGS "-std=c++11")

set (CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../)
install (TARGETS minizip DESTINATION lib)
install (FILES ${HEAD_FILES} DESTINATION include/minizip)

target_link_libraries (minizip z)
