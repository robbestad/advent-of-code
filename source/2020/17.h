//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <span>
#include <numeric>
#include <unordered_set>
#include "../include/utils.h"

#ifndef AOC_17_H
#define AOC_17_H
using namespace std;
namespace day17 {
    using Clock = std::chrono::high_resolution_clock;

    pair<size_t,size_t> part1(const vector<string>&input) {
        auto t1 = Clock::now();
        size_t result{0};

        for(auto v:input){

        }

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        return {result,result_time};
    }

    pair<size_t,size_t> part2(const vector<string>&input) {
        auto t1 = Clock::now();
        size_t result{0};
        for(auto v:input){

        }

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        return {result,result_time};
    }

}

#endif //AOC_17_H
