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

    std::ostream &operator<<(std::ostream &out, const SIGNS value) {
        if (value == SIGNS::PLUS) return out << "PLUS";
        if (value == SIGNS::MINUS) return out << "MINUS";
        if (value == SIGNS::MULT) return out << "MULT";
        if (value == SIGNS::DIV) return out << "DIV";
        if (value == SIGNS::NONE) return out << 'NONE';
        return out << endl;
    }

    void consume(std::stack<int64_t> &operands, std::stack<char> &operators) {
        char op = operators.top();
        if (op == '(')
            return;

        operators.pop();

        int64_t a = operands.top();
        operands.pop();
        int64_t b = operands.top();
        operands.pop();

        switch (op) {
            case '*':
                operands.push(a * b);
                break;
            case '+':
                operands.push(a + b);
                break;
            default:
                break;
        }
    }

    int64_t eval(const char *expression, const std::unordered_map<char, int> &precedence) {
        std::stack<int64_t> operands;
        std::stack<char> operators;

        while (*expression) {
            while (*expression == ' ')
                ++expression;

            switch (*expression) {
                case '+':
                case '*':
                    if (!operators.empty() && precedence.at(operators.top()) >= precedence.at(*expression)) {
                        consume(operands, operators);
                    }
                case '(':
                    operators.push(*expression);
                    break;
                case ')':
                    while (operators.top() != '(') {
                        consume(operands, operators);
                    }
                    operators.pop();
                    break;
                default:
                    int n = *expression - '0';
                    while (std::isdigit(expression[1])) {
                        ++expression;
                        n = n * 10 + (*expression - '0');
                    }
                    operands.push(n);
                    break;
            }
            ++expression;
        }
        while (!operators.empty()) {
            consume(operands, operators);
        }

        return operands.top();
    }

    void start(const string &label, const string &path) {
        size_t sum{0};
        const std::unordered_map<char, int> precedence{{'*', 1},
                                                       {'+', 1},
                                                       {'(', 3}};
        std::fstream f{path};
        vector<string> ops;
        string line;
        while (f >> line) {
            {
                //   cout << line << endl;
            }
        }
        auto t1 = Clock::now();
        std::string expression{"2 * 3 + (4 * 5)"};
        cout << eval(expression.c_str(), {{'*', 1},
                                          {'+', 1},
                                          {'(', 3}}) << endl;
        cout << eval(expression.c_str(), {{'*', 1},
                                          {'+', 2},
                                          {'(', 3}}) << endl;
        cout << endl;
        cout << duration_cast<std::chrono::microseconds>(Clock::now() - t1).count() << " ms" << endl;

    }

}

/*
int parse_line(const string &line) {
    int res[line.size()];
    //[[9, '*', [8, '*', [6, '+', 7], '*', [9, '+', 4], '+', 9], '*', 7, '*', 4, '+', 8], []]
    int i{0};


        for (auto l:line) {
            if (l == ' ') continue;
            if (l == '(') {
                string schild{l};
                res[i] = parse_line(schild);
            } else if (l == ')') break;
            else {
                if()
                res[i] = (unsigned char)l-48;
            }
            i++;
        }

    return *res;
  */

#endif //AOC_18_H
