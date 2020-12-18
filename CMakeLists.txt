cmake_minimum_required(VERSION 3.17)
project(aoc)
include_directories(/usr/local/include)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)


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