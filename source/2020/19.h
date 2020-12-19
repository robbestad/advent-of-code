//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
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
                     vector<int> &rule) {

        for (auto next:ruleset.at(ruleAt).first) {
            if (next == 0)
                continue;
            else if (next == 9999)
                rule.emplace_back(1);
            else if (next == 8888)
                rule.emplace_back(0);
            else
                parse_rules(ruleset, next, rule);

        }

    }

    string convertToString(char *a, int size) {
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

        /*
        std::vector<int> rules_numbers;
        std::unordered_set<std::string> rules_strings;
        for (auto r:ruleset) {
            cout << "-----" << endl;
            cout << r.first << ":";
            for (auto x:r.second.first)
                if (x != 0)
                    rules_numbers.emplace(x);
                    //cout << x << " ";
            //cout << "|";
            for (auto x:r.second.second)
                if (x != 0)
                    rules_numbers.emplace(x);
                    //cout << x << " ";
            cout << endl;
        }


        for (auto r:ruleset.at(0).first) {
            for ( auto &rule : rules_numbers ) {
                std::vector<std::string> tmp_strings = { "" };
                for ( auto &item : rule ) {
                    std::vector<std::string> tmp_tmp_strings{};
                    rule_vector[item].convertRules( rule_vector );
                    for ( auto &new_string :
                            rule_vector[item].getStringRules() ) {
                        for ( auto &old_string : tmp_strings ) {
                            tmp_tmp_strings.push_back( old_string +
                                                       new_string );
                        }
                    }
                    tmp_strings = tmp_tmp_strings;
                }
                for ( auto &converted : tmp_strings ) {
                    rules_strings.insert( converted );
                }
            }
        }
*/


        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        print_result(result, result_time
        );


    }


    class Rule {
    public:
        Rule() {
            index = -1;
        }
        explicit Rule( int num ) {
            index = num;
        }

        void addRule( const std::vector<int>& rule ) {
            rules_numbers.push_back( rule );
        }

        void addRule( const std::string &rule ) {
            rules_strings.insert( rule );
        }

        void addRule( char rule ) {
            rules_strings.insert( std::string( 1, rule ) );
        }

        void convertRules( std::vector<Rule> &rule_vector ) {

            if ( !converted ) {
                og_rules_numbers = rules_numbers;
                og_rules_strings = rules_strings;
                for ( auto &rule : rules_numbers ) {
                    std::vector<std::string> tmp_strings = { "" };
                    for ( auto &item : rule ) {
                        std::vector<std::string> tmp_tmp_strings{};
                        rule_vector[item].convertRules( rule_vector );
                        for ( auto &new_string :
                                rule_vector[item].getStringRules() ) {
                            for ( auto &old_string : tmp_strings ) {
                                tmp_tmp_strings.push_back( old_string +
                                                           new_string );
                            }
                        }
                        tmp_strings = tmp_tmp_strings;
                    }
                    for ( auto &cnv : tmp_strings ) {
                        rules_strings.insert(cnv );
                    }
                }
                converted = true;
            }
        }

        [[nodiscard]] const std::unordered_set<std::string> &getStringRules() const {
            return rules_strings;
        }

    private:
        int index;
        bool converted = false;
        std::vector<std::vector<int>> rules_numbers;
        std::unordered_set<std::string> rules_strings;
        std::vector<std::vector<int>> og_rules_numbers;
        std::unordered_set<std::string> og_rules_strings;
    };


    std::pair<std::vector<Rule>, std::vector<std::string>>
    getInput( std::ifstream &file ) {
        std::vector<Rule> rules{};
        std::vector<std::string> strings{};

        std::string str{};
        int index;
        char tmp_c;
        int tmp_int;
        while ( std::getline( file, str ) ) {
            if ( str.empty() )
                break;
            std::stringstream ss( str );
            ss >> index;
            if ( index >= rules.size() ) {
                rules.resize( index + 1 );
            }
            rules[index] = Rule( index );
            ss >> tmp_c;
            ss.get(); // space
            if ( ss.peek() == '"' ) {
                // we assume that rules with letters only have 1 letter
                // and no additional possible rules
                ss >> tmp_c; // "
                ss >> tmp_c;
                rules[index].addRule( tmp_c );
            } else {
                // we assume that no rule with numbers has a char
                std::vector<int> rule;
                while ( ss >> tmp_int ) {
                    rule.push_back( tmp_int );
                    ss.get();
                    if ( ss.peek() == '|' ) {
                        rules[index].addRule( rule );
                        rule.clear();
                        ss.get();
                    }
                }
                rules[index].addRule( rule );
            }
        }
        while ( std::getline( file, str ) ) {
            strings.push_back( str );
        }

        return { rules, strings };
    }

    std::pair<int, std::vector<std::string>>
    tell_treff_del1(const std::vector<std::string> &strings,
                    const std::unordered_set<std::string> &rules ) {
        int ret = 0;
        std::vector<std::string> invalid{};
        for ( auto &string : strings ) {
            if ( rules.find( string ) != rules.end() )
                ret++;
            else
                invalid.push_back( string );
        }
        return { ret, invalid };
    }
    bool tell_treff_del2(const std::string &input, size_t pos, int count42, int count31, const std::vector<Rule> &rules) {
        if(count31 >= count42 && count31 != 0)
            return false;
        if(count31 == 0) {
            for(auto &rule : rules[42].getStringRules()) {
                if(!strncmp(input.c_str() + pos, rule.c_str(), rule.length())) {
                    if(pos + rule.length() == input.length())
                        return false; // we need at least 1 31
                    if(tell_treff_del2(input, pos + rule.length(), count42 + 1, count31, rules))
                        return true;
                }
            }
        }
        for(auto &rule : rules[31].getStringRules()) {
            if(!strncmp(input.c_str() + pos, rule.c_str(), rule.length())) {
                if(pos + rule.length() == input.length()) {
                    if((count31 + 1) < count42)
                        return true;
                    return false;
                }
                if(tell_treff_del2(input, pos + rule.length(), count42, count31 + 1, rules))
                    return true;
            }
        }
        return false;
    }
    int matchPart2(const std::vector<std::string> &strings,
                   const std::vector<Rule> &rules ) {
        int ret = 0;
        for ( const auto& string : strings ) {
            if(tell_treff_del2(string, 0, 0, 0, rules))
                ret++;
        }
        return ret;
    }

    void start2(const string &label, const string &path) {
        std::ifstream input_file( path );
        auto input = getInput( input_file );

        auto &rules = input.first;
        auto &strings = input.second;
        rules[0].convertRules( rules );
        auto t1 = Clock::now();
        auto res = tell_treff_del1(strings, rules[0].getStringRules());
        cout << "\033[13;1m" << res.first << "\033[0m strenger er gyldig for del 1 ";
        cout << "\033[99;1m(" << duration_cast<std::chrono::microseconds>(Clock::now() - t1).count() << " us)" << endl;
        auto t2 = Clock::now();
        res.first += matchPart2(res.second, rules);
        cout << "\033[23;1m" << res.first
                  << "\033[0m strenger er gyldige for del 2 ";
        cout << "\033[23;1m(" << duration_cast<std::chrono::microseconds>(Clock::now() - t2).count() << " us)" << endl;


    }
}

#endif //AOC_19_H
