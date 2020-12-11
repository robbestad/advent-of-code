#include <iostream>
#include <fstream>
#include <vector>
#include "../../include/binaryToDecimal.h"
#include "../../include/parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Angi input-fil som param" << endl;
        exit(1);
    }
    auto v = vector<int>{};
    parse_input_by_line(argv[1], [&](auto &line) {
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
    printf("%i\n", high);
    printf("%lu\n", (v.size() + 1) * (high + low) / 2 - t);
}