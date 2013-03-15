cmake_minimum_required(VERSION 2.8.9)

project (minizip)

# sources
set (SRC_FILES src/zip_package.cpp)
set (HEAD_FILES include/zip_package.h)

# target
add_library (minizip STATIC ${SRC_FILES})

# compile arguments
#set (CMAKE_C_FLAGS "-DIOAPI_NO_64")
add_definitions (-DIOAPI_NO_64)
if (MSVC)
elseif(UNIX)
	set (CMAKE_CXX_FLAGS "-std=c++11 -Wall")
else()
endif()
# includes
include_directories (include)

# link
target_link_libraries (minizip z)

# install
set (CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../)
install (TARGETS minizip DESTINATION lib)
install (FILES ${HEAD_FILES} DESTINATION include/minizip)

