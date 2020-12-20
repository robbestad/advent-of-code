cmake_minimum_required(VERSION 3.17)
project(aoc)
include_directories(
        /usr/local/include
        ./vcpkg/packages/catch2_x64-osx/include
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
        REQUIRED)

find_package(
        range-v3
        CONFIG
        REQUIRED)


set(glm_DIR /Users/sven/source/glm/cmake/glm) # if necessary
find_package(glm REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc "solve.cpp")
target_link_libraries(aoc glm::glm)
target_compile_options(
        aoc
        PUBLIC $<$<CXX_COMPILER_ID:MSVC>:-W4
        -WX
        -analyze
        -wd4702>) # TODO range-v3 error