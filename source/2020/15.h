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

    size_t iterations = 30000000;
    bool is_new(const vector<size_t> &numbers, size_t number) {
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

    pair<size_t, size_t> find_prev(const vector<size_t> &numbers, size_t number) {
        std::vector<size_t> matches;
        size_t n = 0;
        for (auto &elem : numbers) {
            if (elem == number) {
                matches.emplace_back(n);
            }
            n++;
        }
        return pair(matches[matches.size() - 1], matches[matches.size() - 2]);
    }

    void part1(const string &label) {
        auto t1 = Clock::now();
        std::vector<size_t> input{ 7, 14, 0, 17, 11, 1, 2 };
        std::vector<size_t> numbers{};

        numbers.resize(iterations);
        int round = 0;
        for (size_t i = 0; i < input.size() - 1; i++) {
            round++;
            numbers[input[i]] = round;
            iterations--;
        }
        size_t next = 0;
        size_t counter = 0;
        std::cout << iterations << endl;

        
        auto i = numbers.size() + 1;
        size_t prev = input.back();
        //for (auto n = numbers.size() - 1; n <= numbers.size(); n++) {
            for (int i = 0; i < iterations; i++) {
                round++;
            int last = numbers[prev];
            numbers[prev] = round - 1;
            if (last == 0) {
                prev = 0;
            }
            else {
                prev = round - 1 - last;
            }



            /*



            size_t last_number = numbers[n];
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
                cout << endl << "turn " << i << "\t" << last_number << "\t" << (last + 1) << "-" << (prev + 1) << "\t\t"
                     << next
                     << endl;
            }
            i++;
            if (counter++ == 10000){
                cout << i << endl;
                counter=0;
            }
            

            numbers.emplace_back(next);
            if (n > iterations)
                break;
           */
        }

        cout << endl;
        size_t sum{0};

        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        cout << label << ": "
             << prev << " ("
             << result_time << "ms)"
             << endl;
    }


    int part2(const string &label, const std::vector<int> & input, int rounds) {
        auto t1 = Clock::now();

            std::vector<int> memory{};
            memory.resize(rounds);
            int round = 0;
            for (size_t i = 0; i < input.size() - 1; i++) {
                round++;
                memory[input[i]] = round;
                rounds--;
            }
            rounds--;
            round++;
            int prev = input.back();
            for (int i = 0; i < rounds; i++) {
                round++;
                int last = memory[prev];
                memory[prev] = round - 1;
                if (last == 0) {
                    prev = 0;
                }
                else {
                    prev = round - 1 - last;
                }
            }
            size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
            cout << label << ": "
                << prev << " ("
                << result_time << "ms)"
                << endl;
    }
}

#endif //AOC_15_H
