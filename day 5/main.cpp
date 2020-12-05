#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <regex>
#include "../binaryToDecimal.h"
#include "../lesFil.h"

using namespace std;

auto parse(const vector<string> &input) {
    int it = 0;
    vector<int> result;
    do {
        string r = input[it];
        regex zeros("[FL]");
        regex ones("[BR]");
        r = regex_replace(r, zeros, "0");
        r = regex_replace(r, ones, "1");
        result.emplace_back(binaryToDecimal(stoi(r)));
    } while (++it < input.size() - 1);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Angi input-fil som param" << endl;
        exit(1);
    }

    vector<string> inputData = lesFil(argv[1]);

    auto v = parse(inputData);

    sort(v.begin(), v.end());

    cout << v.at(v.size() - 1) << endl;

    for (int it = 0; it < v.size(); it++) {
        if (v[it + 1] - v[it] == 2) {
            cout << v[it] + 1 << endl;
        }
    }

}

