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

    enum class SIGNS {
        PLUS,
        MINUS,
        MULT,
        DIV,
        NONE
    };

    void calculate(SIGNS &op, int &sum, int &digit1, int &digit2, bool reset_operator) {
        if (op != SIGNS::NONE) {
            if (op == SIGNS::PLUS)
                sum = sum + digit1;
            if (op == SIGNS::MINUS)
                sum = sum - digit1;
            if (op == SIGNS::DIV)
                sum = sum / digit1;
            if (op == SIGNS::MULT)
                sum = sum * digit1;
            digit1 = -1;
            digit2 = -1;
            if (reset_operator)
                op = SIGNS::NONE;
        }
    }

    int calculate_parens(int parens_level, vector<std::pair<int, vector<int>>> &digits,
                         vector<std::pair<int, vector<SIGNS>>> &calc_ops) {
        int result{0};
        for (int n = 0; n < digits[parens_level].second.size(); n++) {
            if (n > 0 && n % 2 != 0) {
                auto op = calc_ops[parens_level].second[n-1];
                if (op == SIGNS::PLUS) cout << "OP " << "PLUS" << endl;
                else if (op == SIGNS::MINUS) cout << "OP " << "MINUS" << endl;
                else if (op == SIGNS::MULT) cout << "OP " << "MULT" << endl;
                else if (op == SIGNS::DIV) cout << "OP " << "DIV" << endl;
                else{
                    op=SIGNS::PLUS;
                    cout << "****** ***** ****** WHAT IS OP " << endl;
                }

                if (op == SIGNS::PLUS)
                    result += digits.at(parens_level).second[n - 1] + digits.at(parens_level).second[n];
                if (op == SIGNS::MINUS)
                    result += digits.at(parens_level).second[n - 1] - digits.at(parens_level).second[n];
                if (op == SIGNS::DIV)
                    result += digits.at(parens_level).second[n - 1] / digits.at(parens_level).second[n];
                if (op == SIGNS::MULT)
                    result += digits.at(parens_level).second[n - 1] * digits.at(parens_level).second[n];
            }
        }
        return result;
    }

    void set_parens(vector<std::pair<int, vector<SIGNS>>> &my_ops, SIGNS op, int parens_level) {
        vector<SIGNS> vec_signs;
        if (!my_ops.empty()) {
            if (my_ops.size() >= parens_level) {
                if (!my_ops[parens_level].second.empty()) {
                    vec_signs = my_ops[parens_level].second;
                }
            }
        }
        vec_signs.emplace_back(op);
        if (my_ops.size() > parens_level)
            my_ops[parens_level].second = vec_signs;
        else
            my_ops.emplace_back(std::pair(parens_level, vec_signs));
        vec_signs.clear();
    }

    int part1(const string &l1) {
        int sum{0};
        int digit1{-1};
        int digit2{-1};
        string t;
        SIGNS op{SIGNS::NONE};
        bool parens{false};
        bool first{true};
        int parens_level{-1};
        vector<int> vec_digits;
        vector<std::pair<int, vector<int>>> digits;
        vector<std::pair<int, vector<SIGNS>>> ops;
        vector<int> temp_sums;

        for (auto l:l1) {
            if (isdigit(l)) {
                if (parens) {
                    if (!digits.empty()) {
                        if (digits.size() >= parens_level) {
                            try {
                                if (!(digits[parens_level].second.empty())) {
                                    vec_digits = digits[parens_level].second;

                                }
                            } catch (std::exception &ex) {
                                cout << "-->" << ex.what();
                            }
                        }
                    }
                    vec_digits.emplace_back(l - 48);
                    if (digits.size() > parens_level)
                        digits[parens_level].second = vec_digits;
                    else
                        digits.emplace_back(std::pair(parens_level, vec_digits));
                    vec_digits.clear();

                } else {
                    if (digit1 == -1) {
                        if (!first)
                            digit1 = l - 48;
                        else {
                            sum = l - 48;
                            first = false;
                        }
                    }
                }
            }
            if (l == '*') {
                if (parens) {
                    set_parens(ops, SIGNS::MULT, parens_level);
                } else {
                    op = SIGNS::MULT;
                }
            }
            if (l == '-') {
                if (parens) {
                    set_parens(ops, SIGNS::MINUS, parens_level);
                } else {
                    op = SIGNS::MINUS;
                }
            }
            if (l == '/') {
                if (parens) {
                    set_parens(ops, SIGNS::DIV, parens_level);
                } else {
                    op = SIGNS::DIV;
                }
            }
            if (l == '+') {
                if (parens) {
                    set_parens(ops, SIGNS::PLUS, parens_level);
                } else {
                    op = SIGNS::PLUS;
                }
            }

            if (l == '(') {
                parens_level++;
                parens = true;
            }
            if (l == ')') {
                cout << "parens_level: " << parens_level << endl;
                if (parens_level == 0) {
                    sum += calculate_parens(parens_level, digits, ops);

                    int temp_sum{0};
                    if (temp_sums.size() > parens_level) {
                        temp_sum = temp_sums.back();
                        cout << "temp_sum: " << temp_sum << endl;

                        temp_sums.pop_back();
                        int res{0};
                        int d = digits[0].second[0];
                        SIGNS o = ops[0].second[0];

                        if (o == SIGNS::MULT)
                            res += d * temp_sum;
                        if (o == SIGNS::PLUS)
                            res += d + temp_sum;
                        if (o == SIGNS::MINUS)
                            res += d - temp_sum;
                        if (o == SIGNS::DIV)
                            res += d / temp_sum;
                        cout << "d: " << d << endl;
                        cout << "RES: " << res << endl;
                        sum += res;
                    }

                } else {
                    int temp_sum{0};
                    temp_sum = calculate_parens(parens_level, digits, ops);

                    temp_sums.emplace_back(temp_sum);
                }
                digits[parens_level].second.clear();
                ops[parens_level].second.clear();
                parens_level--;
                if (parens_level < 0) {
                    parens = false;
                }
            }

            if (l == ' ') {
                if (digit1 >= 0)
                    if (!parens)
                        if (op != SIGNS::NONE) {
                            calculate(op, sum, digit1, digit2, false);
                            op = SIGNS::NONE;
                        }
                if (parens) {

                }
            }
        }

        cout << "S*UM1: " << sum << endl;
        if (op != SIGNS::NONE && digit1 > 0) {
            calculate(op, sum, digit1, digit2,
                      true);
        }
        cout << "S*UM2: " << sum << endl;

        return sum;
    }

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

        //cout << part1("2 * 3 + (4 * 5)") << endl;
        auto res = part1("1 + (2 * 3) + (4 * (5 + 6))");
        cout << "part 1: " << res << endl;
        cout << duration_cast<std::chrono::microseconds>(Clock::now() - t1).count() << " ms" << endl;
        /*
        auto t1 = Clock::now();
        cout << endl << label << ": "
             << sum
             << " (compute: "
             << duration_cast<milliseconds>(Clock::now() - t1).count() << " us)"
             << endl;
    */

    }

}


#endif //AOC_18_H
