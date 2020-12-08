cmake_minimum_required(VERSION 3.17)
project(aoc)
include_directories(/usr/local/include)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc
        "solve.cpp"
        "source/days/7.h"
        source/include/binaryToDecimal.h source/include/lesFil.h source/include/parser.h source/include/split.h source/include/tokenize.h source/days/8.h source/include/utils.h source/days/8_2.h)
