//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include "../include/utils.h"
#include "../include/common.h"

#define DEBUG true

#ifndef AOC_23_H
#define AOC_23_H
namespace day23 {
    using Clock = std::chrono::high_resolution_clock;

    int find_destination(vector<int> &prev_cups, int input, int crt_try) {
        int destination;
#if DEBUG
        cout << "dst?:\t";
        cout << destination;
        cout << endl;
#endif
        bool dst_found{false};
        while (!dst_found) {
            dst_found = true;
            for (int n{0}; n < prev_cups.size(); n++) {
                if (dst_found) {
                    if (prev_cups[n] == destination) dst_found = false;
                }
            }
            if (!dst_found) {
                --crt_try;
                if (crt_try < 0) {
                    crt_try = 8;
                }
                destination = utils::get_digit(input, crt_try);
            }
        }
#if DEBUG
        cout << "dst!:\t";
        cout << destination;
        cout << endl;
#endif
        return destination;
    }

    std::pair<vector<int>, std::string>
    play(int input, int iterator, int length, vector<int> prev_cups) {
        vector<int> pickedup;
        int destination;
        int current_cup;
        vector<int> numbers = utils::get_digits(input);
        vector<int> picked_cups;
        std::deque<int> number_qu{};
        std::deque<int> next_qu{};
        current_cup = utils::get_digit(input, iterator);
        int crt_try{current_cup - 1};
        destination = crt_try;
        cout << "prv:\t";
        for (auto p:prev_cups) cout << p;
        cout << endl;

        cout << "cup:\t" << current_cup << endl;
        prev_cups.emplace_back(current_cup);

        for (int n = 0; n < length; n++) {
            number_qu.push_back(numbers[n]);
        }

        for (int n = iterator + 1; n < iterator + 4; n++) {
            if (n < 9) {
                picked_cups.emplace_back(numbers[n]);
                prev_cups.emplace_back(numbers[n]);
            } else {
                picked_cups.emplace_back(numbers[n - 8]);
                prev_cups.emplace_back(numbers[n]);
            }
        }

        destination = find_destination(prev_cups, input, crt_try);
#if DEBUG
        if (iterator == 0) assert(destination == 2);
        if (iterator == 1) assert(destination == 7);
        if (iterator == 2) assert(destination == 3);
#endif

        cout << "pck:\t";
        for (auto p:picked_cups) cout << p;
        cout << endl;

        picked_cups.emplace_back(current_cup);
        picked_cups.emplace_back(destination);
        utils::remove_intersection(picked_cups, numbers);
        cout << "nmb:\t";
        for (auto p:numbers) cout << p;
        cout << endl;

        size_t nextn{0};
        next_qu.clear();
        for (int n = 0; n < length; n++) {
            if (n == iterator) {
                next_qu.push_back(current_cup);
            } else if (n == destination - 1)
                next_qu.push_back(destination);
            else if (n == destination) {
                next_qu.push_back(picked_cups[0]);
                next_qu.push_back(picked_cups[1]);
                next_qu.push_back(picked_cups[2]);
                n += 2;
            } else {
                if (numbers.size() > nextn) {
                    cout << "legger til " << numbers[nextn] << endl;
                    next_qu.push_back(numbers[nextn]);
                }
                nextn++;
            }
        }

        std::string out;
        for (auto q:next_qu) {
            out += std::to_string(q);
        }
        //out = out.substr(0, 9);
        cout << endl << "out:\t" << out << endl;

        return std::make_pair(picked_cups, out);
    }

    void start(const string &lbl, int input) {
        auto t1 = Clock::now();
        int result{0};
        int it{0};
        int move{0};
        vector<int> prev_cups;
        vector<int> pickup;
        input = 389125467;

        do {
            cout << endl << "move:\t" << move + 1 << endl;
            cout << "inpt:\t" << input << endl;
            auto[picked_cups, next] = play(input, it, 9, prev_cups);
            prev_cups = picked_cups;
            if (move + 1 == 2) cout << "ctrl:\t" << 325467891 << endl;

            input = stoi(next);
            cout << "next:\t" << input << endl;

            if (move + 1 == 1) assert(input == 328915467);
            if (move + 1 == 2) assert(input == 325467891);
            if (move + 1 == 3) assert(input == 725891346);


            it++;
            if (it > 8)
                it = 0;

        } while (move++ <= 1);

        cout << result;
    }

}

#endif //AOC_23_H
