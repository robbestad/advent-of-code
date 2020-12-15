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

    bool is_new(const vector<long> &numbers, long number) {
        bool found{false};
        for (auto it = numbers.begin(); it != numbers.end(); ++it) {
            if (std::next(it) == numbers.end()) {
                break;
            }
            if (*it == number) {
                found = true;
            }
        }
        return !found;
    }

    pair<long, long> find_prev(const vector<long> &numbers, long number) {
        std::vector<long> matches;
        long n = 0;
        for (auto &elem : numbers) {
            if (elem == number) {
                matches.emplace_back(n);
            }
            n++;
        }
        return pair(matches[matches.size() - 1], matches[matches.size() - 2]);
    }

    void part1(const string &label, const std::vector<long> &input, int iterations) {
        auto t1 = Clock::now();
        std::vector<long> numbers = input;
        long next = 0;
        size_t sum{ 0 };
        long counter = 0;
        auto i = numbers.size() + 1;
        for (auto n = numbers.size() - 1; n <= numbers.size(); n++) {
            long last_number = numbers[n];
            if (is_new(numbers, last_number)) {
                next = 0;
                if (1 == iterations - numbers.size()) {
                    cout << "turn " << i << "\t" << last_number << "\t" << "new" << "*" << "new" "\t\t"
                         << next << endl;
                   
                }
                i++;
                numbers.emplace_back(next);
                continue;
            }

            auto[last, prev] = find_prev(numbers, last_number);
            next = (last + 1) - (prev + 1);

            if (1 == iterations - numbers.size()) {
             sum = next;
               /*
                cout << endl << "turn " << i << "\t" << last_number << "\t" << (last + 1) << "-" << (prev + 1) << "\t\t"
                     << next
                     << endl;
               */
            }
            i++;
            if (counter++ == 1000000) {
                cout << i << endl;
                counter = 0;
            }

            numbers.emplace_back(next);
            if (sum>0 || n>iterations)
                break;

        }

        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        cout << label << ": "
             << sum << " ("
             << result_time << "ms) ("
             << iterations << ")"
             << endl;
    }


    void part2(const string &label, const std::vector<size_t> &input, int iterations) {
        auto t1 = Clock::now();
        std::vector<size_t> numbers{};
        numbers.resize(iterations);
        int round = 0;
        for (size_t i = 0; i < input.size() - 1; i++) {
            round++;
            numbers[input[i]] = round;
            iterations--;
        }
        iterations--;
        round++;

        size_t prev = input.back();
        size_t next{0};
        for (int i = 0; i < iterations; i++) {
            round++;
            size_t last_number = numbers[prev];
            numbers[prev] = round - 1;
            if (last_number == 0)
                prev = 0;
            else
                prev = round - 1 - last_number;
        }

        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        cout << label << ": "
             << prev << " ("
             << result_time << "ms) ("
             << iterations << ")"
             << endl;
    }

}

#endif //AOC_15_H
