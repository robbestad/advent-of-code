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
using ull = unsigned long long;
using Clock = std::chrono::high_resolution_clock;

namespace day14 {

    void recursive_find_addresses(std::string addr, std::string& mask, int start_index,
                                  std::vector<std::string>* addr_list) {
        for (int i = start_index; i < mask.length(); ++i) {
            if (mask.at(i) == 'X') {
                addr.at(i) = '0';
                recursive_find_addresses(addr, mask, i + 1, addr_list);
                addr.at(i) = '1';
                recursive_find_addresses(addr, mask, i + 1, addr_list);
                return;
            }
        }
            addr_list->emplace_back(addr);
    }

    void update_addresses(std::vector<std::string>& addr_list, ull value,
                          std::map<ull, ull>* mem) {
        for (auto const& addr : addr_list) {
            mem->insert_or_assign(std::bitset<36>(addr).to_ullong(), value);
        }
    }

    void part2(const string &label, const string &path) {
        auto t_read = Clock::now();
        std::string command, eq_string, mask, value;
        std::fstream f{path};
        std::map<ull, ull> memory;
        std::vector<std::string> addr_list;
        while (f >> command >> eq_string >> value) {
            if (command == "mask")
                mask = value;
            else {
                const auto mem_addr{std::stol(command.substr(4, command.size() - 5))};
                std::string addr = std::bitset<36>(mem_addr).to_string();
                for (int i = 0; i <  mask.length(); ++i) {
                    if (mask.at(i) == '1') {
                        addr[i] = '1';
                    }
                }
                recursive_find_addresses(addr, mask, 0, &addr_list);
                update_addresses(addr_list, stoull(value), &memory);
                addr_list.clear();
            }
        }
        size_t read_time = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t_read).count();

        auto t1 = Clock::now();

        ull sum{};
        auto mem_sum = [](const auto &memory, ull &sum) {
            for (const auto &mem : memory)
                sum += mem.second;
            return sum;
        };
        mem_sum(memory, sum);

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        cout << label << ": "
             << sum
             << " (3442819875191) "
             << " (compute: "
             << result_time << " us)"
             << " (parse: "
             << read_time << " us)"
             << endl;
    }

}

#endif //AOC_14_2_H
