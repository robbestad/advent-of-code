//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <span>
#include <numeric>
#include <unordered_set>
#include "../include/utils.h"

#ifndef AOC_22_H
#define AOC_22_H
using namespace std;
namespace day22 {
    vector<size_t> nums;
    vector<string> strings;

    void parse_input(const string &path) {
        parse_input_by_line(path, [&](const auto &line) {
            nums.emplace_back(stol(line));
            strings.emplace_back(line);
        });
    };

    size_t part1() {


        return -1;
    }

    size_t part2() {
       

        return -1;
    }

}

#endif //AOC_22_H
