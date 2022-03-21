cmake_minimum_required(VERSION 3.17)
project(bitset)

set(CMAKE_CXX_STANDARD 14)

add_executable(bitset runner.cpp bitset.hpp bitset_kruk.cpp)
target_link_libraries(bitset cppunit)