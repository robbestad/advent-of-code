#include <iostream>
#include <fstream>
#include <vector>
#include "../include/binaryToDecimal.h"
using namespace std;

namespace day5 {

    long unsigned int solve() {
        auto v = vector<int>{};
        std::string path{"source/day_5/input"};
        parse_input_by_line(path, [&](auto &line) {
            transform(line.begin(), line.end(), line.begin(), [](auto c) {
                if (c == 'B' || c == 'R') {
                    return '1';
                }
                return '0';
            });
            v.emplace_back(binaryToDecimal(stoi(line)));
        });

        int t = 0;
        int low = INT_MAX;
        int high = 0;
        for (int it : v) {
            if (it < low) low = it;
            if (it > high) high = it;
            t += it;
        }
        //printf("%i\n", high);
        //printf("%lu\n", (v.size() + 1) * (high + low) / 2 - t);
        return (v.size() + 1) * (high + low) / 2 - t;
    }
}