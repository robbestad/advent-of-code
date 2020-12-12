cmake_minimum_required(VERSION 3.17)
project(aoc)
include_directories(/usr/local/include)
include_directories(input)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc
        "solve.cpp"
        "source/2020/7.h"
        source/include/binaryToDecimal.h source/include/lesFil.h source/include/parser.h source/include/split.h source/include/tokenize.h source/2020/8.h source/include/utils.h source/2020/8_2.h)
