//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include "../include/utils.h"

#ifndef AOC_19_H
#define AOC_19_H
using namespace std;
namespace day19 {
    using std::string;
    using std::vector;
    using std::unordered_set;
    using std::cout;
    using std::endl;
    using std::unordered_map;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using Clock = std::chrono::high_resolution_clock;

    void print_result(const string &result, size_t result_time) {
        cout << result
             << " (compute: "
             << result_time << " us)"
             << endl;
    }

    enum Vals {
        A = 9999,
        B = 8888
    };

    size_t array_to_num(int arr[], int n) {
        char str[6][3];
        int i;
        char number[13] = {'\n'};

        for (i = 0; i < n; i++)sprintf(str[i], "%d", arr[i]);
        for (i = 0; i < n; i++)strcat(number, str[i]);

        i = atoi(number);
        return i;
    }

    void parse_line(const char *line) {
        std::stack<size_t> rules;
        std::unordered_map<size_t, string> ruleset;
        int t[10]{};
        std::fill_n(t, 10, 0);
        int curr_rule{0};

        cout << endl;
        int i = 0;
        while (*line) {
            while (*line == ' ')
                ++line;
            switch (*line) {
                case ':':
                    curr_rule = array_to_num(t, i);
                    cout << "***" << curr_rule << "***";
                    ruleset.emplace(curr_rule, "rule");
                    std::fill_n(t, i, 0);
                    i = 0;
                    break;
                default:
                    if (isdigit(*line))
                        t[i] = *line - '0';
                    // cout << *line << "-";
            }
            i++;
            ++line;
        }
        for (auto r:ruleset)
            cout << r.first << ":" << r.second << endl;
    }

    void parse_rules(const unordered_map<int, std::pair<std::array<int, 3>, std::array<int, 3>>> &ruleset,
                     int ruleAt,
                      std::stack<char> &rule) {

        for (auto next:ruleset.at(ruleAt).first) {
            if (next == 0)
                continue;
            else if (next == 9999)
                rule.push('a');
            else if (next == 8888)
                rule.push('b');
            else
                parse_rules(ruleset, next,  rule);

        }

    }

    string convertToString(char* a, int size)
    {
        int i;
        string s = "";
        for (i = 0; i < size; i++) {
            s = s + a[i];
        }
        return s;
    }



    void start(const string &label, const string &path) {
        cout << label << endl;
        auto t1 = Clock::now();
        std::fstream f{path};
        string result;
        unordered_map<int, std::pair<std::array<int, 3>, std::array<int, 3>>> ruleset;
        string input, line, num, rule1, rule2;
        bool stop_parsing_numbers = false;
        std::fstream file(path);
        while (std::getline(file, input)) {
            line = regex_replace(input, (regex) "\"", "");
            auto splits = utils::split(line, " ");
            int rule_num{0};
            std::array<int, 3> rule_num_rules1{0, 0, 0};
            std::array<int, 3> rule_num_rules2{0, 0, 0};
            if (splits[0].starts_with("a") || splits[0].starts_with("b")) {
                cout << splits[0] << endl;
            } else if (!stop_parsing_numbers && isdigit(splits[0][0])) {
                string rule = regex_replace(splits[0], (regex) ":", "");
                rule_num = stoi(rule);
                bool first_set_of_rules = true;
                int n = 0;
                for (int i = 1; i < splits.size(); i++) {
                    if (splits[i] == "|") {
                        first_set_of_rules = false;
                        n = 0;
                        continue;
                    }
                    if (first_set_of_rules) {
                        try {
                            if (splits[i] == "a")
                                rule_num_rules1[0] = Vals::A;
                            else if (splits[i] == "b")
                                rule_num_rules1[0] = Vals::B;
                            else {
                                int val = stoi(splits[i]);
                                rule_num_rules1[n++] = val;
                            }
                        } catch (std::exception &e) {
                            cout << e.what() << endl;
                            cout << splits[i] << endl;
                        }
                    } else {
                        try {
                            if (splits[i] == "a" || splits[i] == "b") {
                                rule_num_rules1[0] = Vals::B;
                            } else {
                                int val = stoi(splits[i]);
                                rule_num_rules2[n++] = val;
                            }

                        } catch (std::exception &e) {
                            cout << e.what() << endl;
                            cout << splits[i] << endl;
                        }
                    }
                }
                ruleset.emplace(rule_num, std::make_pair(rule_num_rules1, rule_num_rules2));
            }


            if (!line[0]) {
                stop_parsing_numbers = true;
                continue;
            }
            //parse_line(line.c_str());
        }


        for (auto r:ruleset) {
            cout << "-----" << endl;
            cout << r.first << ":";
            for (auto x:r.second.first)
                if (x != 0)
                    cout << x << " ";
            cout << "|";
            for (auto x:r.second.second)
                if (x != 0)
                    cout << x << " ";
            cout << endl;
        }
        cout << endl << "____GO_____" << endl;
        vector<string> valid_strings;
        std::stack<char> rule;
        for (auto r:ruleset.at(0).first) {
            parse_rules(ruleset, r, rule);
            string vr{};
            for(auto& x:rule){
                vr+=x;

            }

            valid_strings.emplace_back(vr);
            rule.pop();
        }
        string rs=convertToString(rule,rule.size());

        for(auto x:valid_strings)
            cout << x << endl;
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        print_result(result, result_time
        );
    }

}

#endif //AOC_19_H
