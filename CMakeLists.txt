cmake_minimum_required(VERSION 3.17)
project(aoc)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
include_directories(
        c:/Users/svena/source/vcp/packages
)

find_package(
        Catch2
        CONFIG
        REQUIRED)

find_package(
        fmt
        CONFIG
        REQUIRED)

find_package(
        glm
        CONFIG
        REQUIRED
        )


add_executable(aoc "solve.cpp" )
#target_link_libraries(aoc PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)
target_link_libraries(aoc glm)
target_compile_options(
        aoc
        PUBLIC $<$<CXX_COMPILER_ID:MSVC>:-W4
        -WX
        -analyze
        -wd4702>) # TODO range-v3 error