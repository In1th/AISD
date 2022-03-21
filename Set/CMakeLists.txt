cmake_minimum_required(VERSION 3.17)
project(Set)



set(CMAKE_CXX_STANDARD 14)

add_executable(Set runner.cpp set_ostafin.cpp set.hpp )
target_link_libraries(Set cppunit)