//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include <regex>
#include <map>
#include <set>
#include "../include/utils.h"
#include "../include/binaryToDecimal.h"

#ifndef AOC_14_H
#define AOC_14_H
using namespace std;
namespace day14 {
    using Clock = std::chrono::high_resolution_clock;

    struct mem {
        size_t address{0};
        size_t value{0};

        mem() = default;

        mem(size_t address, size_t value) : address{address}, value{value} {}
    };

    void part1(const string &label, const vector<string> &input) {
        auto t1 = Clock::now();
        size_t result{0};

        string mask{};
        string mask2{};
        vector<mem> bits{};
        set<unsigned long long> address{};
        map<unsigned long long, unsigned long long> adresses;

        for (auto v:input) {
            if (v[1] == 'a') {
                auto s = utils::split(v, "= ");
                mask = s[1];
                // char sign = mask.c_str()[0];
                mask2 = regex_replace(mask, (regex) "X", "0");
                // string value = regex_replace(mask, (regex) "X", "0");
            }

            if (v[1] == 'e') {
                auto s = utils::split(v, "mem");
                auto s2 = utils::split(s[1], "= ");
                string s3 = s2[0];
                s3.erase(std::remove(s3.begin(), s3.end(), ' '), s3.end());
                s3.erase(std::remove(s3.begin(), s3.end(), '['), s3.end());
                s3.erase(std::remove(s3.begin(), s3.end(), ']'), s3.end());
                mem b{};
                b.value = stoi(s2[1]);
                b.address = stoi(s3);
                bits.emplace_back(b);
                address.insert(b.address);
            }
        }

        for (auto a:address) {
            adresses.emplace(a, 0);
        }

        string ret_mask = mask;
        for (auto t:bits) {
            cout << "bef: " << mask << endl;
            auto dec = utils::toBinary(t.value);
            string rdec(dec.rbegin(), dec.rend());
            string rev_mask(mask.rbegin(), mask.rend());

            for (int n = 0; n < dec.length(); n++) {
                if (rev_mask[n] == 0) {
                    rev_mask[n] = 0;
                } else if (rev_mask[n] == 'X') {
                    auto num = rdec[n];
                    rev_mask[n] = num;
                }
            }
            string temp_mask(rev_mask.rbegin(), rev_mask.rend());
            ret_mask = temp_mask;

            auto res_mask = regex_replace(ret_mask, (regex) "X", "0");
            //unsigned long long mask_to_long = std::bitset<64>(res_mask).to_ullong();

            adresses[t.address] = binaryToDecimal(stoi(res_mask));

            cout << "aft: " << regex_replace(ret_mask, (regex) "X", "0") << endl;
            cout << "---" << endl;
        }

        int sum{0};
        for (auto a:adresses) {
            sum += a.second;
        }

        //3018030 er for lavt
        //664710 er for lavt
        //3563300 er for lavt

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        cout << label << ": "
             << sum << " ("
             << result_time << " ms)"
             << endl;
    }

    void part2(const string &label, const vector<string> &input) {
        auto t1 = Clock::now();
        size_t result{0};
        for (auto v:input) {

        }

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        cout << label << ": "
             << result << " ("
             << result_time << ")"
             << endl;
    }
}

#endif //AOC_14_H
