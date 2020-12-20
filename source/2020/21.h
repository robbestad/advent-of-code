//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include "../include/utils.h"

#ifndef AOC_21_H
#define AOC_21_H
using namespace std;
namespace day21 {
    using std::string;
    using std::vector;
    using std::unordered_set;
    using std::cout;
    using std::endl;
    using std::unordered_map;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using Clock = std::chrono::high_resolution_clock;

    void part1(const vector<string> &input) {
    }

    void part2(const vector<string> &input) {
    }

    string
    getInput( std::ifstream &file ) {
        std::string str{};
        int index;
        while (std::getline(file, str)) {
            if (str.empty())
                break;
            std::stringstream ss(str);
            cout << str << endl;
        }



        return str;
    }

    void start(const string &label, const string &path) {
        std::ifstream input_file(path);
        auto input = getInput(input_file);
    }

}

#endif //AOC_21_H
