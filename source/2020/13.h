//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <climits>
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

    struct bus {
        int idx = 0;
        int id = 0;

        bus() = default;

        bus(int index, int bus_id) : idx{index}, id{bus_id} {}
    };

    struct schedule_structure {
        int current_time = 0;
        std::vector<bus> bus_ids;
    };

    void part1(const string &label, const vector<string> &input) {
        auto t1 = Clock::now();
        size_t result{0};
        auto departure_time = stol(input[0]);
        auto times = utils::split(input[1], ",");
        unordered_map<int, vector<int>> schedulemap;
        vector<bus> schedule;
        int i{0};
        for (const auto &v:times) {
            if (v != "x") {
                schedulemap.emplace(pair(stoi(v), 0));
                bus b;
                b.idx = i++,
                b.id = stoi(v);
                schedule.emplace_back(b);
            }
        }
        schedule_structure s;
        s.current_time = 0;
        s.bus_ids = std::move(schedule);

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

        cout << label << ": " << result << " ("
             << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << "ns)" << endl;


        t1 = Clock::now();
        std::vector<int> wait;
        wait.reserve(s.bus_ids.size());
        std::transform(s.bus_ids.begin(), s.bus_ids.end(), std::back_inserter(wait),
                       [t = s.current_time](bus b) { return b.id - (t % b.id); });
        auto min_wait = std::min_element(wait.begin(), wait.end());
        auto idx = std::distance(wait.begin(), min_wait);
        cout << label << ": "
             << *min_wait * s.bus_ids[idx].id
             << " ("
             << std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t1).count() << "ns)" << endl;

    }


}

#endif //AOC_13_H
