cmake_minimum_required(VERSION 3.5)
project(calculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -g")

set(EXPR_FILES expr.cpp expr.hpp tools.hpp)
set(PROGRAM_FILES program.cpp program.hpp ${EXPR_FILES})

set(TEST_EXPR ${EXPR_FILES} testExpr.cpp)
add_executable(testExpr.exe ${TEST_EXPR})

set(TEST_PROGRAM ${PROGRAM_FILES} testProgram.cpp)
add_executable(testProgram.exe ${TEST_PROGRAM})

add_executable(calculator.exe ${PROGRAM_FILES} calculator.cpp)