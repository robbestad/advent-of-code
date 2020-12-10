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

    void parse_input(const string &path) {
        parse_input_by_line(path, [&](const auto &line) {
            jolts.emplace_back(stoi(line));
        });
        sort(jolts.begin(), jolts.end());
    };

    size_t part1() {
        sort(jolts.begin(), jolts.end());
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

    uint64_t count() {
        size_t combinations[jolts.size()];
        combinations[0] = 1;
        int i = 0;
        do {
            size_t sum = 0;
            if (jolts[i] <= 3) sum++;
            int j = i - 1;
            do {
                if (jolts[i] - jolts[j] <= 3) {
                    sum += combinations[j + 1];
                }
                j--;
            } while (j > 0);
            combinations[i + 1] = sum;
        } while (i++ < jolts.size());
        return combinations[jolts.size()];
    }


    size_t part2fast() {
        //from https://github.com/Otaku619/AoC2020Solutions/blob/master/Day10Part2.cpp
        long long a[(long)1e6];
        jolts.push_back(jolts[jolts.size() - 1] + 3);
        jolts.insert(jolts.begin(), 0);
        a[0] = 1;
        for (long long jolt : jolts)
            a[jolt] += (jolt > 0 ? a[jolt - 1] : 0) + (jolt > 1 ? a[jolt - 2] : 0) +
                       (jolt > 2 ? a[jolt - 3] : 0);
        return a[jolts[jolts.size() - 1]];
    }

    size_t part2() {
        return count();
    }

}

#endif //AOC_10_H
