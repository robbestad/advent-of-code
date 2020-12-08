//
// borrowed from https://github.com/fredrikpe/advent-of-code-2020/blob/master/cpp/input_parser.h
//
#ifndef AOC_PARSER_H
#define AOC_PARSER_H

template<class Function>
void parse_input_by_line(const std::string &path, Function f) {
    std::ifstream file(path);

    auto line = std::string{};
    while (std::getline(file, line)) {
        f(line);
    }
}

template<class Function>
void parse_input_grouped(const std::string &path, Function f) {
    std::ifstream file(path);
    std::vector<std::string> data;
    if (file.fail()) {
        std::cerr << "Fil kunne ikke åpnes" << std::endl;
        file.close();
        exit(1);
    }

    std::string row;
    std::string temp;
    int num = 0;

    while (getline(file, row)) {
        num++;
        temp += row;
        if (row.empty()) {
            data.push_back(temp);
            temp = "";
        }
    }
    data.push_back(temp);
    f(data);
    file.close();
}


template<class Function>
void parse_input(const std::string &path, Function f) {
    std::ifstream fil{path};
    std::string s;
    getline( fil, s, '\0');
    fil.close();
    f(s);
}
#endif //AOC_PARSER_H
