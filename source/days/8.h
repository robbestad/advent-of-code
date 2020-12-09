//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <regex>
#include "../include/utils.h"

#ifndef AOC_8_H
#define AOC_8_H
namespace day8 {
    struct ops {
        string op{};
        int value{};
        char sign{};
    };

    std::map<int, std::vector<ops>> instructions;

    void parse_input(const string &path) {
        int i = 0;
        parse_input_by_line(path, [&](const auto &line) {
            std::vector<std::string> out = utils::split(line, " ");
            char sign = out[1].c_str()[0];
            string value = regex_replace(out[1], (regex) "[+-]", "");

            ops ops;
            ops.value = stoi(value);
            ops.sign = sign;
            ops.op = (string) out[0];
            instructions[i++].push_back(ops);
        });

    };

    int solve() {
        int acc = 0;
        int ptr = 0;
        bool cnt = true;
        vector<int> visited;
        do {
            auto current_instruction = instructions.at(ptr);
            auto item = current_instruction[0];

            auto it = find(visited.begin(), visited.end(), ptr);
            if (it != visited.end()) {
                cnt = false;
                continue;
            } else
                visited.emplace_back(ptr);

            if (item.op == "nop") {
                ptr++;
                continue;
            }

            if (item.op == "acc") {
                if (item.sign == '-')
                    acc -= item.value;
                else
                    acc += item.value;
                ptr++;
                continue;
            }
            if (item.op == "jmp") {
                if (item.sign == '-')
                    ptr -= item.value;
                else
                    ptr += item.value;
                continue;
            }
        } while (cnt);
        return acc;
    }

}

#endif //AOC_8_H
