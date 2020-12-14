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

    void part1(const string &label, const string &path) {
        auto t_read = Clock::now();
        std::string input;
        std::fstream f{path};
        size_t result{0};
        std::map<ull, ull> memory, memory2;

        while (f >> input) {

        }

        auto t1 = Clock::now();

        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        cout << label << ": "
             << result << " ("
             << result_time << ")"
             << endl;
    }

    void part2(const string &label, const string &path) {
        auto t1 = Clock::now();
        size_t result{0};
        std::string input;
        std::fstream f{path};
        std::map<ull, ull> memory, memory2;

        while (f >> input) {

        }

        t1 = Clock::now();


        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        cout << label << ": "
             << result << " ("
             << result_time << ")"
             << endl;
    }
}

#endif //AOC_15_H
