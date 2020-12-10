//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <span>
#include <numeric>
#include <cmath>
#include <list>
#include <unordered_map>
#include "../include/utils.h"

#ifndef AOC_2019_1_H
#define AOC_2019_1_H
using namespace std;
namespace day2019_1 {
    vector<size_t> parse_input(const string &path) {
        vector<size_t> nums;
        parse_input_by_line(path, [&](const auto &line) {
            nums.emplace_back(stoi(line));
        });
        return nums;
    };

    size_t part1(const vector<size_t> &nums) {
        size_t fuel{0};
        for (auto num:nums) {
            fuel += floor(num / 3) - 2;
        }
        return fuel;
    }

    void calculate_fuel_memoized(size_t mass, vector<size_t> &sum,unordered_map<int,int>&memo) {
        double fuel{0};
        if (memo[mass])
            fuel = memo[mass];
        else {
            fuel = floor(mass / 3) - 2;
            memo.insert(pair(mass,fuel));
            memo[mass] = fuel;
        }
        if (fuel <= 0)
            return;
        sum.emplace_back(fuel);
        return calculate_fuel_memoized(fuel, sum,memo);
    }

    void calculate_fuel(size_t mass, vector<size_t> &sum) {
        double fuel = floor(mass / 3) - 2;
        if (fuel <= 0)
            return;
        sum.emplace_back(fuel);
        return calculate_fuel(fuel, sum);
    }

    bool test() {
        bool ok = true;
        vector<size_t> sum;
        calculate_fuel(14, sum);
        if (accumulate(sum.begin(), sum.end(), (size_t) 0) == 2) cout << "-OK-";
        else ok = false;
        sum.clear();
        calculate_fuel(100756, sum);
        if (accumulate(sum.begin(), sum.end(), (size_t) 0) == 50346) cout << "-OK-";
        else ok = false;
        sum.clear();
        calculate_fuel(1969, sum);
        if (accumulate(sum.begin(), sum.end(), (size_t) 0) == 966) cout << "-OK-";
        else ok = false;
        return ok;
    }

    size_t part2(const vector<size_t> &nums) {
        unordered_map<int,int>memo;
        vector<size_t> sum;
        for (auto fuel:nums) {
            calculate_fuel_memoized(fuel, sum,memo);
        }
        return accumulate(sum.begin(), sum.end(), (size_t) 0);
    }

}

#endif //AOC_10_H
