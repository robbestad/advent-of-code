#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "../../include/split.h"
#include "../../include/parser.h"

using namespace std;

namespace day6 {


    int part1() {
        int sum = 0;
        /** del 1 **/
        parse_input_grouped("source/day_6/input", [&](const auto &buffer) {
            for (auto t:buffer) {
                std::set<char> chars;
                t.erase(std::remove(t.begin(), t.end(), ' '), t.end());
                t.erase(
                        std::remove_if(
                                t.begin(),
                                t.end(),
                                [&chars](char i) {
                                    if (chars.count(i)) { return true; }

                                    chars.insert(i);
                                    return false;
                                }
                        ),
                        t.end()
                );
                sum += t.length();
            }
        });
        return sum;
    }

    int part2() {
        /** del 2 **/
        int sum = 0;
        set<char> result;
        set<char> temp;
        bool first = true;
        parse_input_by_line("source/day_6/input", [&](const auto &line) {
            if (line.empty()) {
                sum += result.size();
                result.clear();
                first = true;
            }
            if (!line.empty()) {
                if (first) {
                    for (auto c: line) {
                        result.insert(c);
                    }
                    first = false;
                }

                temp.clear();
                for (auto c: line) {
                    if (result.count(c) > 0) {
                        temp.insert(c);
                    }
                }
                result = temp;
            }
        });
        sum += result.size();
        return sum;
    }
}
