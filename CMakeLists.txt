cmake_minimum_required(VERSION 3.17)
project(aoc)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc
        "day 6/main.cpp" binaryToDecimal.h lesFil.h parser.h split.h tokenize.h)
