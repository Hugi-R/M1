cmake_minimum_required(VERSION 3.5)
project(calculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
set(SOURCE_FILES expr.cpp expr.hpp)
add_executable(calculator ${SOURCE_FILES})