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
#include <iostream>
#include <numeric>
#include <vector>

#ifndef AOC_13_2_H
#define AOC_13_2_H
using namespace std;


namespace day13 {
    using Clock = std::chrono::high_resolution_clock;

    struct bus {
        int pos = 0;
        int value = 0;

        bus() = default;

        bus(int index, int bus_value) : pos{index}, value{bus_value} {}
    };


    int64_t mul_inv(int64_t a, int64_t b) {
        int64_t b0 = b;
        int64_t t, q;
        int64_t x0 = 0, x1 = 1;
        if (b == 1) return 1;
        while (a > 1) {
            q = a / b;
            t = b, b = a % b, a = t, t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        //if (x1 < 0) x1 += b0;
        return x1;
    }

    int64_t remainder(int64_t a, int64_t b) {
        using pair = std::pair<int64_t, int64_t>;
        pair r{a, b};
        pair s{1, 0};
        pair t{0, 1};

        while (r.second != 0) {
            auto q = r.first / r.second;
            r = {r.second, r.first - q * r.second};
            s = {s.second, s.first - q * s.second};
            t = {t.second, t.first - q * t.second};
        }
        return s.first;
    }

    int64_t crt(const std::vector<bus> &buses) {
        int64_t prod{1};
        for (auto b:buses) {
            prod *= b.value;
        }
        int64_t sum = 0;
        int64_t sum2 = 0;
        for (auto b : buses) {
            sum += b.pos * mul_inv(prod / b.value, b.value) * (prod / b.value);
            sum2 += b.pos * remainder(prod / b.value, b.value) * (prod / b.value);
        }
        return abs(sum % prod);
        //return (sum > 0 ? sum : (-sum + prod)) % prod;
    }

    void part2(const string &label, const vector<string> &input) {
        auto times = utils::split(input[1], ",");
        unordered_map<int, int> schedules;
        vector<int> schedule;
        size_t pos{0};

        for (const auto &v:times) {
            if (v == "x") {
                pos++;
                continue;
            }
            schedules.emplace(pair(stoi(v), pos++));
        }

        std::vector<bus> bus_values;
        bus_values.reserve(schedules.size() + 1);
        for (const auto &[k, v]:schedules) {
            bus b;
            b.value = k;
            b.pos = v;
            bus_values.emplace_back(b);
        }


        auto t_1 = Clock::now();
        auto sum = crt(bus_values);
        auto t_2 = Clock::now();
        cout << label
             << " (crt): "
             << sum << " ("
             << std::chrono::duration_cast<std::chrono::nanoseconds>(t_2 - t_1).count()
             << "ns)"
             << endl;

        auto t1 = Clock::now();
        unsigned long long timestep{100000000000000};//hint fra adventofcode
        unsigned long long step{1};
        for (const auto &[k, v]:schedules) {
            while ((timestep + v) % k != 0)
                timestep += step;
            step *= k;
        }
        auto t2 = Clock::now();
        cout << label << " (sieve): "
             << timestep << " ("
             << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << "ns)"
             << endl;
    }
}

#endif //AOC_13_2_H
