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

namespace day18 {
    using std::string;
    using std::vector;
    using std::unordered_set;
    using std::cout;
    using std::endl;
    using std::unordered_map;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using Clock = std::chrono::high_resolution_clock;

    enum class Operators {
        PLUS,
        MINUS,
        MULT,
        DIV,
        NONE
    };

    void calculate(Operators &op, int &sum, int &digit1, int &digit2, bool reset_operator) {
        if (op != Operators::NONE) {
            if (op == Operators::PLUS)
                sum = sum + digit1;
            if (op == Operators::MINUS)
                sum = sum - digit1;
            if (op == Operators::DIV)
                sum = sum / digit1;
            if (op == Operators::MULT)
                sum = sum * digit1;
            digit1 = -1;
            digit2 = -1;
            if (reset_operator)
                op = Operators::NONE;
        }
    }

    int calculate_parens(std::vector<int> &digits, std::vector<Operators> &operators) {
        int result{0};

        for (int n = 0; n < digits.size(); n++) {
            if (n > 0 && n % 2 != 0) {
                if (operators[n - 1] == Operators::PLUS)
                    result += digits[n - 1] * digits[n];
                if (operators[n - 1] == Operators::MINUS)
                    result += digits[n - 1] * digits[n];
                if (operators[n - 1] == Operators::DIV)
                    result += digits[n - 1] * digits[n];
                if (operators[n - 1] == Operators::MULT)
                    result += digits[n - 1] * digits[n];
            }
        }
        return result;
    }

    size_t part1(const string &l1) {
        int sum{0};
        int digit1{-1};
        int digit2{-1};
        string t;
        Operators op{Operators::NONE};
        bool parens{false};
        bool first{true};
        size_t parens_level{0};
        vector<int> digits;
        vector<Operators> operators;

        for (auto l:l1) {
            if (isdigit(l)) {
                if (parens) {
                    digits.emplace_back(l - 48);
                }
                if (digit1 == -1) {
                    if (!first)
                        digit1 = l - 48;
                    else {
                        sum = l - 48;
                        first = false;
                    }
                }
            }
            if (l == '*') {
                op = Operators::MULT;
                if (parens) {
                    operators.emplace_back(op);
                }
            }
            if (l == '-') {
                op = Operators::MINUS;
                if (parens) {
                    operators.emplace_back(op);
                }
            }
            if (l == '/') {
                op = Operators::DIV;
                if (parens) {
                    operators.emplace_back(op);
                }
            }
            if (l == '+') {
                op = Operators::PLUS;
                if (parens) {
                    operators.emplace_back(op);
                }
            }

            if (l == '(') {
                parens_level++;
                parens = true;
            }
            if (l == ')') {
                parens_level--;
                sum += calculate_parens(digits, operators);
                op = Operators::NONE;
                if (parens_level == 0)
                    parens = false;
            }

            if (l == ' ') {
                if (digit1 >= 0)
                    if (!parens)
                        if (op != Operators::NONE) {
                            calculate(op, sum, digit1, digit2, false);
                        }
                if (parens) {

                }
            }
        }

        if (op != Operators::NONE) {
            calculate(op, sum, digit1, digit2, true);
        }

        return sum;
    }

#ifndef UNIT_TESTING

    void start(const string &label, const string &path) {
        size_t sum{0};
        std::fstream f{path};
        vector<string> ops;
        string line;
        while (f >> line) {
            {
                //   cout << line << endl;

            }
        }
        auto t1 = Clock::now();

        cout << part1("2 * 3 + (4 * 5)") << endl;
        cout << part1("1 + (2 * 3) + (4 * (5 + 6))") << endl;

        /*
        auto t1 = Clock::now();
        cout << endl << label << ": "
             << sum
             << " (compute: "
             << duration_cast<milliseconds>(Clock::now() - t1).count() << " us)"
             << endl;
*/

    }

#else

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <sstream>


    TEST_CASE("Test with zero", "[classic]")
{
    REQUIRE(fizzbuzz(0) == "0");
}
#endif
}


#endif //AOC_18_H
