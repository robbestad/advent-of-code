//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include "../include/utils.h"

#ifndef AOC_16_H
#define AOC_16_H
using namespace std;
namespace day16 {
    using Clock = std::chrono::high_resolution_clock;

    void part1(const string &label, const string &path) {
        auto t1 = Clock::now();
        size_t result{0};
        auto t_read = Clock::now();
        std::string input;
        std::fstream f{path};
        std::vector<std::string> addr_list;
        while (f >> input) {

        }
        size_t read_time = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t_read).count();

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        cout << label << ": "
             << result
             << " (compute: "
             << result_time << " us)"
             << " (parse: "
             << read_time << " us)"
             << endl;
    }


}

#endif //AOC_16_H
