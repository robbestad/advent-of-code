//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <functional>
#include <chrono>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <type_traits>
#include "../include/utils.h"

#ifndef AOC_13_H
#define AOC_13_H
using namespace std;
namespace day13 {
    using Clock = std::chrono::high_resolution_clock;

    pair<size_t, size_t> part1(const vector<string> &input) {
        auto t1 = Clock::now();
        size_t result{0};
        auto departure_time = stol(input[0]);
        auto times = utils::split(input[1], ",");
        unordered_map<int, vector<int>> schedulemap;
        vector<int> schedule;
        for (const auto &v:times) {
            if (v != "x") {
                schedulemap.emplace(pair(stoi(v), 0));
            }
        }

        unordered_map<int, vector<int>> expanded_schedulemap;
        for (const auto &s:schedulemap) {
            int time = s.first;
            vector<int> bus_times;
            do {
                time += s.first;
                bus_times.emplace_back(time);
            } while (time < departure_time + s.first);
            expanded_schedulemap.emplace(s.first, bus_times);
        }
        auto distance{0};
        auto lowest{INT_MAX};
        auto the_bus{0};
        for (const auto &s:expanded_schedulemap) {
            //cout << s.first << ": ";
            for (const auto &t:s.second) {
                distance = t - departure_time;
                if (distance > 0) {
                    if (distance < lowest) {
                        lowest = distance;
                        the_bus = s.first;
                        //cout << distance << " ";
                    }
                }
            }
            //cout << endl;
        }
        result = lowest * the_bus;

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        return {result, result_time};
    }


}

#endif //AOC_13_H
