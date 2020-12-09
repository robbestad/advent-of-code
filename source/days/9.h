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

    size_t part1_alternative_solution() {
        size_t low = 0, high = 25 - 1;
        for (size_t i = 25; i < numbers.size() + 0; i++, low++, high++) {
            if (!find_number(numbers, low, high, numbers[i])) return numbers[i];
        }
        return -1;
    }

    size_t part1() {
        for (size_t i = 25; i < numbers.size(); i++) {
            vector<size_t> prev25(numbers.begin() + (i - 25), numbers.begin() + i + 1);

            bool found = false;
            for (size_t it = 0; it < 25; it++) {
                for (size_t j = it; j < 25; j++) {
                    if (prev25.at(it) + prev25.at(j) == numbers.at(i)) {
                        found = true;
                    }
                }
            }
            if (!found)
                return numbers.at(i);
        }
        return -1;
    }

    size_t part2() {
        size_t number_to_find = 507622668; //eller part1() hvis du vil gjør det treigt.
        vector<size_t> sums(numbers.size());
        partial_sum(numbers.begin(), numbers.end(), sums.begin());
        for (size_t i = 1; i < sums.size(); ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (sums[i] - sums[j] == number_to_find) {
                    const auto minmax = minmax_element(
                            numbers.begin() + j, numbers.begin() + i
                    );
                    return *minmax.second + *minmax.first;
                }
            }
        }

        return -1;
    }

}

#endif //AOC_9_H
