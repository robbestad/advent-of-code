//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#ifndef AOC_UTILS_H
#define AOC_UTILS_H

namespace utils{

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
