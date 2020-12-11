//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <span>
#include <numeric>
#include <unordered_set>
#include "../include/utils.h"

#ifndef AOC_12_H
#define AOC_12_H
using namespace std;
namespace day12 {
    vector<size_t> nums;
    vector<string> strings;

    vector<string> parse_input(const string &path) {
        parse_input_by_line(path, [&](const auto &line) {
            nums.emplace_back(stol(line));
            strings.emplace_back(line);
        });
        return strings;
    };

    size_t part1(const vector<string>&input) {
        for(auto v:input){

        }

        return 0;
    }

    size_t part2(const vector<string>&input) {
        for(auto v:input){

        }

        return 0;
    }

}

#endif //AOC_12_H
