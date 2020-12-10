//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <span>
#include <numeric>
#include <cmath>
#include <unordered_set>
#include "../include/utils.h"

#ifndef AOC_2019_1_H
#define AOC_2019_1_H
using namespace std;
namespace day2019_1 {
    vector<size_t> nums;

    void parse_input(const string &path) {
        parse_input_by_line(path, [&](const auto &line) {
            nums.emplace_back(stoi(line));
        });
    };

    size_t part1() {
        size_t fuel{0};
        for (auto num:nums) {
            fuel += floor(num / 3) - 2;
        }
        return fuel;
    }

    size_t calculate_fuel(size_t mass) {
        double fuel{0};
        double additional_fuel{0};
        do {
            additional_fuel = floor(mass / 3) - 2;
            if (additional_fuel > 0) {
                mass = additional_fuel;
                fuel += additional_fuel;
            } else
                break;
        } while (mass > 0);
        return fuel;
    }
    void test(){
        size_t test1 = calculate_fuel(14);
        if (test1 == 2) cout << "test1 OK" << endl;
        else cout << "test1 NOT OK: " << test1 << endl;
        size_t test2 = calculate_fuel(100756);
        if (test2 == 50346) cout << "test2 OK" << endl;
        else cout << "test2 NOT OK: " << test2 << endl;

        size_t test3 = calculate_fuel(1969);
        if (test3 == 966) cout << "test3 OK" << endl;
        else cout << "test3 NOT OK: " << test3 << endl;
    }

    size_t part2() {
        test();
        size_t fuel=part1();
        for (auto mass:nums) {
            fuel += calculate_fuel(mass);
        }
        if(fuel==9801136) cout<<"wrong: ";
        if(fuel==16339038) cout<<"wrong: ";
        return fuel;
    }

}

#endif //AOC_10_H
