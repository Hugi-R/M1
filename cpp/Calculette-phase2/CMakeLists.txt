cmake_minimum_required(VERSION 3.5)
project(calculator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -g")

set(SOURCE_FILES main.cpp tokenstream.cpp program.cpp prog_function.cpp tokenstream.h program.h prog_function.h)

add_executable(calculator ${SOURCE_FILES})

