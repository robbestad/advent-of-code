//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include "../include/utils.h"

#ifndef AOC_15_H
#define AOC_15_H
using namespace std;
namespace day15 {
    using Clock = std::chrono::high_resolution_clock;

    void part1(const string &label, const vector<string> &input) {
        auto t1 = Clock::now();
        size_t result{0};

        for (auto v:input) {

        }

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        cout << label << ": "
             << result << " ("
             << result_time << ")"
             << endl;
    }

    void part2(const string &label, const vector<string> &input) {
        auto t1 = Clock::now();
        size_t result{0};
        for (auto v:input) {

        }

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        cout << label << ": "
             << result << " ("
             << result_time << ")"
             << endl;
    }
}

#endif //AOC_15_H
