//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include <deque>
#include "../include/utils.h"
#include "../include/common.h"

#ifndef AOC_23_H
#define AOC_23_H
namespace day23 {

    int getDigit(int n, int position) {
        return (n % (int) pow(10, position) - (n % (int) pow(10, position - 1))) / (int) pow(10, position - 1);
    }

    std::pair<size_t, std::string>
    play(size_t input, size_t iterator, size_t length) {
        vector<size_t> pickedup;
        size_t destination;
        size_t current_cup;
        size_t destination_pos;
        vector<size_t> numbers = utils::get_digits(input);
        std::deque<size_t> number_qu{};
        for (size_t n = 0; n < length; n++) {
            number_qu.push_back(numbers[n]);
        }
        for (size_t n = iterator + 1; n < length; n++) {
            if (n < 8)
                pickedup.emplace_back(utils::get_digit(input, n));
            else
                pickedup.emplace_back(utils::get_digit(input, n - 8));
        }
        current_cup = utils::get_digit(input, iterator);
        size_t last{1};
        destination = current_cup - last;
        /*while (destination == last_destination) {
            destination = current_cup - last++;
        }*/
        




        //finn posisjon
        for (size_t n = 0; n < length; n++) {
            if (utils::get_digit(input, n) == destination) {
                destination_pos = n;
            }
        }

        cout << "current cup:" << current_cup << endl;

        //legg tilbake
        std::string out;
        out = "0";
        /*
        for (size_t n = 0; n < (destination - 1); n++) {
            out += std::to_string(utils::get_digit(input, n));
        }
         */
        //out += std::to_string(temp[0]);
        return std::make_pair(destination, out);
    }

    void start(const string &lbl, size_t input) {
        size_t result{0};
        size_t it{0};
        size_t move{0};
        size_t prev{0};
        vector<size_t> pickup;
        input = 389125467;

        std::cout << lbl << std::endl;

        do {
            cout << "move: " << move + 1 << endl;
            cout << input << endl;
            auto[last_destination, next] = play(input, it, 9);
            prev = last_destination;
            input = std::stoi(next);


            it++;
            if (it > 8)
                it = 0;

        } while (move++ < 1);

        cout << result;
    }

}

#endif //AOC_23_H
