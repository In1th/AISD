cmake_minimum_required(VERSION 3.17)
project(tree)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES Tree.hpp)

add_executable(tree main.cpp ${HEADER_FILES})


