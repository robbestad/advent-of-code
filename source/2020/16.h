//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include "../include/utils.h"

#ifndef AOC_16_H
#define AOC_16_H
using namespace std;
namespace day16 {
    using Clock = std::chrono::high_resolution_clock;

    bool num_exists(const vector<int> &numbers, int number) {
        bool found{false};
        for (auto it = numbers.begin(); it != numbers.end(); ++it) {
            if (*it == number) {
                found = true;
            }
        }
        return found;
    }

    void part1(const string &label, const string &path) {
        auto t1 = Clock::now();
        size_t result{0};
        auto t_read = Clock::now();
        std::string range1, type, orstring, range2, tickets;
        std::fstream f{"input/16ranges1.txt"};
        std::vector<std::string> addr_list;
        std::vector<int> valid_nums;
        std::vector<string> valid_tickets;
        while (f >> type >> range1 >> orstring >> range2) {
            if (!range1.empty()) {
                //cout << range1 << range2 << endl;
                auto r = utils::split(range1, "-");
                //cout << r[0] << r[1]<<endl;
                for (int i = stoi(r[0]); i <= stoi(r[1]); i++)
                    valid_nums.emplace_back(i);
                auto r2 = utils::split(range2, "-");
                //cout << r2[0] << r2[1]<<endl;
                for (int i = stoi(r2[0]); i <= stoi(r2[1]); i++)
                    valid_nums.emplace_back(i);
            }
        }
        std::fstream f2{"input/16tickets1.txt"};
        while (f2 >> tickets) {
            auto t = utils::split(tickets, ",");

            for(auto n:t){
                bool found = num_exists(valid_nums, stoi(n));
                if(!found){
                    //cout << n <<",";
                    result+=stoi(n);
                }
            }
        }

        size_t read_time = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t_read).count();

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        cout << endl << label << ": "
             << result
             << " (compute: "
             << result_time << " us)"
             << " (parse: "
             << read_time << " us)"
             << endl;
    }


}

#endif //AOC_16_H
