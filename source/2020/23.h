//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include "../include/utils.h"
#include "../include/common.h"

#ifndef AOC_23_H
#define AOC_23_H
namespace day23 {
    using Clock = std::chrono::high_resolution_clock;

    int getDigit(int n, int position) {
        return (n % (int) pow(10, position) - (n % (int) pow(10, position - 1))) / (int) pow(10, position - 1);
    }

    std::string play(size_t input, size_t num, size_t length) {
        vector<size_t> temp;
        size_t destination;
        size_t current_cup;
        current_cup = utils::get_digit(input, 0);
        current_cup=2;
        destination = current_cup - 1;

        cout << "current cup:" << current_cup << endl;
        cout << "destination:" << destination << endl;

        for (int n = 1; n < length; n++) {
            temp.emplace_back(utils::get_digit(input, n));
        }

        //legg tilbake
        std::string out;
        out = std::to_string(utils::get_digit(input, 0));
        for (size_t n = 1; n < (destination - 1); n++) {
            out += std::to_string(utils::get_digit(input, n));
        }
        out += std::to_string(temp[0]);
        out += std::to_string(temp[1]);
        out += std::to_string(temp[2]);

        for (size_t n = (destination+2); n < length; n++) {
            out += std::to_string(utils::get_digit(input, n));
        }

        return out;
    }

    void start(const string &lbl, size_t input) {
        auto t1 = Clock::now();
        size_t result{0};
        size_t round{0};
        vector<size_t> pickup;
        input = 389125467;

        do {
            cout << "round: " << round + 1 << endl;
            cout << input << endl;
            auto next = play(input, 3, 9);
            input = stoi(next);
            cout << "next: " << next;
            cout << endl;
            cout << endl;


        } while (round++ < 2);

        cout << result;
    }

}

#endif //AOC_23_H
