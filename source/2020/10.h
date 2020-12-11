//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <span>
#include <numeric>
#include <unordered_set>
#include <queue>
#include "../include/utils.h"
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

#ifndef AOC_10_H
#define AOC_10_H
using namespace std;
namespace day10 {
    vector<size_t> jolts;

    vector<size_t> parse_input(const string &path) {
        parse_input_by_line(path, [&](const auto &line) {
            jolts.emplace_back(stoi(line));
        });
        sort(jolts.begin(), jolts.end());
        return jolts;
    };

    size_t part1() {
        size_t highest = jolts.at(jolts.size() - 1) + 3;
        size_t lowest = jolts.at(0);
        vector<size_t> ones;
        vector<size_t> threes;

        ones.emplace_back(lowest);
        threes.emplace_back(highest);

        for (auto jolt:jolts) {
            if (jolt == lowest)
                continue;
            if (jolt - lowest == 1) {
                lowest = jolt;
                ones.emplace_back(lowest);
                continue;
            }
            if (jolt - lowest == 3) {
                lowest = jolt;
                threes.emplace_back(lowest);
                continue;
            }
        }
        //cout << endl << "ones: " << ones.size() << endl;
        //cout << "threes: " << threes.size() << endl;
        return ones.size() * threes.size();
    }

    size_t count(const vector<size_t> &input) {
        size_t combinations[jolts.size()];
        combinations[0] = 1;
        int i = 0;
        do {
            size_t sum = 0;
            if (input[i] <= 3) sum++;
            int j = i - 1;
            do {
                if (input[i] - input[j] <= 3) {
                    sum += combinations[j + 1];
                }
            } while (j-- > 0);
            combinations[i + 1] = sum;
        } while (i++ < input.size());
        return combinations[input.size()];
    }


    size_t part2fast( vector<size_t> &input) {
        //from https://github.com/Otaku619/AoC2020Solutions/blob/master/Day10Part2.cpp
        int max = 1e6;
        long long a[max];
        input.push_back(input[input.size() - 1] + 3);
        input.insert(input.begin(), 0);
        a[0] = 1;
        for (long long jolt : input)
            a[jolt] += (jolt > 0 ? a[jolt - 1] : 0) + (jolt > 1 ? a[jolt - 2] : 0) +
                       (jolt > 2 ? a[jolt - 3] : 0);
        return a[input[input.size() - 1]];
    }


}

#endif //AOC_10_H
