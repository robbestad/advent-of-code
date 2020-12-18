//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <array>
#include <unordered_set>
#include <unordered_map>
#include <regex>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include "../include/Math.h"
#include "../include/utils.h"

#ifndef AOC_18_H
#define AOC_18_H
using std::string;
using std::unordered_set;
using std::unordered_map;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

namespace day18 {
    using Clock = std::chrono::high_resolution_clock;

    string convertToString(const char *a) {
        string s(a);
        return s;
    }

    enum class operators {
        PLUS,
        MINUS,
        MULT,
        DIV,
        NONE
    };

    size_t part1(const vector<string> &line) {
        string l1 = "2 * 3 + (4 * 5)";
        //string l = "(2 + 6) * 2 + 2 + 4";
        int sum{0};
        int tsum{};
        int digit1{-1};
        int digit2{-1};
        string t;
        operators op{operators::NONE};

        bool parens = false;
        for (auto l:l1) {
            if (isdigit(l)) {
                if (digit1 == -1)
                    digit1 = l - 48;
            }
            if (l == '*')
                op = operators::MULT;
            if (l == '-')
                op = operators::MINUS;
            if (l == '/')
                op = operators::DIV;
            if (l == '+')
                op = operators::PLUS;

            if (l == '(')
                parens = true;
            if (l == ')')
                parens = false;

            if (l == ' ') {
                if (digit1 >= 0)
                    if (op != operators::NONE) {
                        if (op == operators::PLUS)
                            sum = sum + digit1;
                        if (op == operators::MINUS)
                            sum = sum - digit1;
                        if (op == operators::DIV)
                            sum = sum / digit1;
                        if (op == operators::MULT)
                            sum = sum * digit1;
                        digit1 = -1;
                        digit2 = -1;
                        //op = operators::NONE;
                        cout << sum << ",";
                    }
                if (parens) {
                }
            }
        }
        if (op != operators::NONE) {
            if (op == operators::PLUS)
                sum = sum + digit1;
            if (op == operators::MINUS)
                sum = sum - digit1;
            if (op == operators::DIV)
                sum = sum / digit1;
            if (op == operators::MULT)
                sum = sum * digit1;
            digit1 = -1;
            digit2 = -1;
            op = operators::NONE;
            cout << sum << ":";
        }

        cout << "----";
        return sum;
    }


    void start(const string &label, const string &path) {
        std::fstream f{path};
        vector<string> ops;
        string line;
        while (f >> line) {
            {
                //   cout << line << endl;

            }
        }
        auto t1 = Clock::now();
        cout << endl << label << ": "
             << part1(ops)
             << " (compute: "
             << duration_cast<milliseconds>(Clock::now() - t1).count() << " us)"
             << endl;


    }


}

#endif //AOC_18_H
