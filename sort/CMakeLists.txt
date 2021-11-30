cmake_minimum_required(VERSION 3.17)
project(sort)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-I/usr/include/python2.7 -lpython2.7")

add_executable(sort main.cpp)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(main.cpp ${PYTHON_LIBRARIES})