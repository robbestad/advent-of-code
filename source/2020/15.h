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
    using ull = unsigned long long;

    struct Number {
        int value;
        int position;

        Number() = default;

        Number(int position, int value) : position{position}, value{value} {}
    };

    bool is_new(const vector<int> &numbers, int number) {
        vector<int> vec = numbers;
        vec.pop_back();
        bool found{false};
        std::vector<int> matches;
        for (auto &elem : vec) {
            if (elem == number) {
                found = true;
            }
        }
        return !found;
    }

    std::vector<int> find_matches(const vector<int> &numbers, int number) {
        vector<int> vec = numbers;
        vec.pop_back();

        std::vector<int> matches;
        int n = 0;
        for (auto &elem : vec) {
            if (elem == number) {
                Number game_number{n, number};
                matches.emplace_back(n);
            }
            n++;
        }
        return matches;
    }


    pair<int, int> find_prev(const vector<int> &numbers, int number) {
        std::vector<int> matches;
        int n = 0;
        for (auto &elem : numbers) {
            if (elem == number) {
                matches.emplace_back(n);
            }
            n++;
        }
        return pair(matches[matches.size()-1], matches[matches.size()-2]);
    }

    void part1(const string &label, const string &path) {
        auto t_read = Clock::now();
        std::vector numbers{7,14,0,17,11,1,2};
        int next = -1;
        auto i = numbers.size() + 1;
        for (auto n = numbers.size() - 1; n <= numbers.size(); n++) {
            int last_number = numbers[n];
            if (is_new(numbers, last_number)) {
                next = 0;
                cout << "turn " << i++ << "\t" << last_number << "\t" << "new" << "*" << "new" "\t\t" << next << endl;
                numbers.emplace_back(next);
                continue;
            }

            auto[last, prev] = find_prev(numbers, last_number);
            next = (last + 1) - (prev + 1);
            cout << "turn " << i++ << "\t" << last_number << "\t" << (last + 1) << "-" << (prev + 1) << "\t\t" << next
                 << endl;
            numbers.emplace_back(next);

            if (n > 2020)
                break;

        }

        cout << endl;
        auto t1 = Clock::now();
        size_t sum{0};

        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        cout << label << ": "
             << sum << " ("
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
