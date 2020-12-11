//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#ifndef AOC_UTILS_H
#define AOC_UTILS_H

namespace utils{

    template<typename T>
    std::vector<T> read_all_lines(std::string path) {
        std::string line;
        std::vector<T> lines;
        std::ifstream f(path);
        while (std::getline(f, line)) {
            if constexpr (std::is_same<T, std::string>::value) {
                lines.push_back(line);
            } else if constexpr (std::is_same<T, int>::value) {
                lines.push_back(std::stoi(line));
            } else if constexpr (std::is_same<T, long long>::value) {
                lines.push_back(std::stoll(line));
            }
        }
        f.close();
        return lines;
    }

    std::vector<std::vector<std::string>> separate_datasets(std::vector<std::string> input) {
        std::vector<std::vector<std::string>> dataSets = {};
        std::vector<std::string> dataSet = {};
        for (auto& line : input) {
            if (line.length() == 0) {
                dataSets.push_back(dataSet);
                dataSet = {};
            } else {
                dataSet.push_back(line);
            }
        }
        if (dataSet.size() != 0) {
            dataSets.push_back(dataSet);
        }
        return dataSets;
    }

    std::vector<std::string> split (std::string s, std::string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    }
}
#endif //AOC_UTILS_H
