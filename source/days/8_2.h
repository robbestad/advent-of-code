//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#ifndef AOC_8_2_H
#define AOC_8_2_H
namespace day8_2 {
    struct ops {
        string op{};
        int value{};
        char sign{};
    };

    string op;
    vector<ops> line;
    int value;
    char sign;

    std::map<int, std::vector<ops>> instructions;
    std::map<int, std::vector<ops>> copy_of_instructions;

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
        int size = instructions.size();
        int it = 0;
        do {
            // nullstill for hver iterasjon inntil en
            // konfigurasjon er funnet som terminerer

            int ptr = 0;
            int acc = 0;
            unordered_map<int, int> visited;
            copy_of_instructions = instructions;

            line = copy_of_instructions[it];
            op = line[0].op;
            value = copy_of_instructions[it][0].value;

            if (op == "acc") continue;
            if (op == "nop")
                copy_of_instructions[it][0].op = "jmp";
            if (op == "jmp")
                copy_of_instructions[it][0].op = "nop";

            while (true) {
                if (visited.find(ptr) != visited.end()) {
                    break;
                }
                if (ptr == size) {
                    return acc;
                }

                visited[ptr] = 1;
                line = copy_of_instructions[ptr];
                op = line[0].op;
                value = line[0].value;
                sign = line[0].sign;

                if (op == "acc") {
                    if (sign == '+')
                        acc += value;
                    else
                        acc -= value;

                    ptr++;
                }
                if (op == "jmp") {
                    if (sign == '+')
                        ptr += value;
                    else
                        ptr -= value;
                }

                if (op == "nop")
                    ptr++;
            }
        } while (it++ < size);
        return -1;
    }
}
#endif //AOC_8_2_H
