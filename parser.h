//
// borrowed from https://github.com/fredrikpe/advent-of-code-2020/blob/master/cpp/input_parser.h
//

#ifndef AOC_PARSER_H
#define AOC_PARSER_H

#endif //AOC_PARSER_H
template<class Function>
void parse_input_by_line(const std::string& path, Function f) {
    std::ifstream file(path);

    auto line = std::string{};
    while (std::getline(file, line)) {
        f(line);
    }
}