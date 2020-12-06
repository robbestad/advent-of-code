//
// Created by Sven Anders Robbestad on 06/12/2020.
//
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#ifndef AOC_TOKENIZE_H
#define AOC_TOKENIZE_H
std::vector<std::string> tokenize(
        const std::string& str,
        const std::regex& re)
{
    std::sregex_token_iterator it{ str.begin(),
                                   str.end(), re, -1 };
    std::vector<std::string> tokenized{ it, {} };

    // Additional check to remove empty strings
    tokenized.erase(
            std::remove_if(tokenized.begin(),
                           tokenized.end(),
                           [](std::string const& s) {
                               return s.empty();
                           }),
            tokenized.end());

    return tokenized;
}
#endif //AOC_TOKENIZE_H
