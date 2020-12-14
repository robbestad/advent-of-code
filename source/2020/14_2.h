//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include <regex>
#include <map>
#include <set>
#include <utility>
#include "../include/utils.h"
#include "../include/binaryToDecimal.h"

#ifndef AOC_14_2_H
#define AOC_14_2_H
namespace day14 {
    using ull = unsigned long long;
    using Clock = std::chrono::high_resolution_clock;

    std::vector<ull> apply_mask_bitshift2(ull address, std::string mask) {
        ull zeros_mask = (1ULL << 37) - 1;
        ull ones_mask{};
        for (int i{}; i < mask.size(); ++i)
            if (mask[mask.size() - i - 1] == '1') ones_mask += 1ULL << i;
            else if (mask[mask.size() - i - 1] == 'X') zeros_mask ^= 1ULL << i;
/*
        cout << "0: " << mask << endl;
        cout << "1: " << address << endl;
        cout << "2: " << utils::toBinary(ones_mask) << endl;
        cout << "3: " << utils::toBinary(zeros_mask) << endl;
        cout << "4: " << utils::toBinary((address | ones_mask) & zeros_mask) << endl;
*/
        std::vector<ull> addresses{(address | ones_mask) & zeros_mask};
        for (int i{}; i < mask.size(); ++i)
            if (mask[mask.size() - i - 1] == 'X')
                for (ull j{}, size{addresses.size()}; j < size; ++j)
                    addresses.push_back(addresses[j] | (1ULL << i));

        return addresses;
    }

    void part2(const string &label, const string &path) {
        auto t_read = Clock::now();
        std::string command, eq_string, value, mask;
        std::fstream f{path};
        std::map<ull, ull> memory, memory2;
        while (f >> command >> eq_string >> value) {
            if (command == "mask")
                mask = value;
            else {
                const auto address{std::strtol(command.substr(4, command.size() - 5).c_str(), nullptr, 10)};
                const auto &addresses = apply_mask_bitshift2(address, mask);
                for (const auto &ad : addresses)
                    memory2[ad] = std::strtol(value.c_str(), nullptr, 10);
            }
        }
        size_t read_time = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t_read).count();

        auto t1 = Clock::now();

        ull sum{};
        auto mem_sum = [](const auto &memory) {
            ull sum{};
            for (const auto &mem : memory)
                sum += mem.second;
            return sum;
        };
        sum = mem_sum(memory2);

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        cout << label << ": "
             << sum
             << " (compute: "
             << result_time << " us)"
             << " (parse: "
             << read_time << " us)"
             << endl;
    }

}

#endif //AOC_14_2_H
