cmake_minimum_required(VERSION 3.5)
project(calculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -g")

set(TEST_EXPR expr.cpp expr.hpp tools.hpp testExpr.cpp)
add_executable(testExpr.exe ${TEST_EXPR})

set(TEST_PROGRAM program.cpp program.hpp expr.hpp expr.cpp tools.hpp testProgram.cpp)
add_executable(testProgram.exe ${TEST_PROGRAM})