//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <span>
#include <numeric>
#include <unordered_set>
#include "../include/utils.h"

#ifndef AOC_9_H
#define AOC_9_H
using namespace std;
namespace day9 {
    vector<long> numbers;

    void parse_input(const string &path) {
        parse_input_by_line(path, [&](const auto &line) {
            numbers.emplace_back(stol(line));
        });
    };

    bool find_number(std::vector<long> &v, int start, int low, long max) {
        unordered_set<long> numset;
        for (size_t iterator = start; iterator <= low; iterator++) {
            long sum = max - v[iterator];
            if (numset.count(sum) == 1) return true;
            numset.insert(v[iterator]);
        }
        return false;
    }

    size_t part1() {
        size_t low = 0, high = 24;
        for (size_t i = 25; i <= numbers.size(); i++, low++, high++) {
            if (!find_number(numbers, low, high, numbers[i])) return numbers[i];
        }
        return -1;
    }

    size_t part2() {
        size_t target = 507622668; // eller part1();
        auto left = 0;
        auto right = 0;
        auto sum = numbers.at(0);
        do {
            if (sum < target) {
                right += 1;
                sum += numbers.at(right);
            } else if (sum > target) {
                sum -= numbers.at(left);
                left += 1;
            } else {
                const auto minmax = minmax_element(
                        numbers.begin() + left, numbers.begin() + right
                );
                return *minmax.second + *minmax.first;
            }
        } while (true);
    }


}

#endif //AOC_9_H
