#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "../include/split.h"
#include "../include/parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Angi input-fil som param" << endl;
        exit(1);
    }
    int sum = 0;


    /** del 1 **/
    parse_input_grouped(argv[1], [&](const auto &buffer) {
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
    cout << sum << endl;

    /** del 2 **/
    sum = 0;
    parse_input(argv[1], [&](const auto &buffer) {
        auto lines = split_lines(buffer);
        set<char> result;
        set<char> temp;
        bool first = true;
        for (auto line:lines) {
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
        }
        sum += result.size();
    });
    cout << sum << endl;
}