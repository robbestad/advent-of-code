//
// Created by Sven Anders Robbestad on 06/12/2020.
//

#ifndef AOC_SPLIT_H
#define AOC_SPLIT_H

std::vector<std::string_view> split(std::string_view str, std::string_view delimiter, bool include_empty) {
    std::vector<std::string_view> parts;

    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        parts.emplace_back(str.substr(0, pos));
        str.remove_prefix(pos + delimiter.length());
    }

    if (str != "" || include_empty) {
        parts.emplace_back(str);
    }

    return parts;
}

std::vector<std::string_view> split_lines(std::string_view input) {
    return split(input, "\n", false);
}

#endif //AOC_SPLIT_H
