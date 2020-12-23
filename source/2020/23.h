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

    std::pair<int, std::string>
    play(int input, int num, int iterator, int length, int last_destination) {
        vector<int> pickedup;
        int destination;
        int current_cup;
        int destination_pos;
        vector<int> numbers = utils::get_digits(input);
        std::deque<int> number_qu{};
        std::deque<int> next_qu{};
        current_cup = utils::get_digit(input, iterator);
        int last{1};
        destination = current_cup - last;
        int current_it{iterator};
        int count{0};

        for (int n = 0; n < length; n++) {
            number_qu.push_back(numbers[n]);
            count++;
        }

        next_qu.push_back(current_cup);
        next_qu.push_back(destination);

        for (int n = destination - 1; n < length; n++) {
            if (n < 9) {
                if (numbers[n] != destination)
                    next_qu.push_back(numbers[n]);
                iterator = n;
            } else {
                if (numbers[n - 9] != destination)
                    next_qu.push_back(numbers[n - 9]);
                iterator = n - 8;
            }
            count++;
        }

        std::string out;
        for (auto q:next_qu) {
            out += std::to_string(q);
        }

        return std::make_pair(destination, out);
    }

    void start(const string &lbl, int input) {
        auto t1 = Clock::now();
        int result{0};
        int it{0};
        int move{0};
        int prev{0};
        vector<int> pickup;
        input = 389125467;

        do {
            cout << "move:\t" << move + 1 << endl;
            cout << "inpt:\t" << input << endl;
            auto[last_destination, next] = play(input, 3, it, 9, prev);
            prev = last_destination;
            input = stoi(next);
            cout << "next:\t" << input;
            cout << endl << endl;

            if(move+1==1) assert(input==328915467);
            if(move+1==2) assert(input==325467891);


            it++;
            if (it > 8)
                it = 0;

        } while (move++ <= 0);

        cout << result;
    }

}

#endif //AOC_23_H
