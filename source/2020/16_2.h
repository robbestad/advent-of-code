//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <set>
#include <map>
#include <vector>
#include <unordered_set>
#include <utility>
#include "../include/utils.h"

#ifndef AOC_16_2_H
#define AOC_16_2_H

using std::string;
using std::pair;
using std::vector;
using std::map;
using std::cout;
using std::endl;

namespace day16 {
    using Index = std::size_t;
    constexpr Index SENTRY = SIZE_MAX;

    struct Rule {
        string label;
        pair<int, int> lb;
        pair<int, int> ub;
        Index i = SENTRY;

        Rule() = default;

        Rule(string lbl, pair<int, int> lb, pair<int, int> ub) :
                label{std::move(lbl)}, lb{std::move(lb)}, ub{std::move(ub)} {}
    };

    struct Ticket {
        std::vector<int> values;

        Ticket() = default;

        explicit Ticket(vector<int> values) :
                values{std::move(values)} {}
    };

    struct Field {
        Index i{};
        std::vector<int> values;
    };


    bool valid_ticket(const vector<Rule> &rules, int number) {
        bool found{false};
        for (const auto &rule: rules) {
            if (number >= rule.lb.first && number <= rule.lb.second ||
                number >= rule.ub.first && number <= rule.ub.second) {
                found = true;
            }
        }
        return found;
    }

    auto falls_in_ranges(const int n, const Rule &rules) {
        if ((rules.lb.first <= n && n <= rules.lb.second) ||
            (rules.ub.first <= n && n <= rules.ub.second))
            return true;
        return false;
    }

    auto all_fall(const std::vector<int> &fv, const Rule &r) {
        for (const auto v : fv) {
            if (!falls_in_ranges(v, r)) {
                return false;
            }
        }
        return true;
    }


    auto decipher_fields(std::vector<Rule> vr, const std::vector<Ticket> &vt)
    // fields can match multiple rules, need to eliminate rules with one match
    {
        std::deque<Field> df;
        for (Index i = 0; i < vt.front().values.size(); ++i) {
            std::vector<int> field_vals;
            for (const auto &j : vt)
                field_vals.push_back(j.values[i]);
            df.push_back(Field{i, field_vals});
        }

        while (!df.empty()) {
            auto f = df.front();
            std::vector<Rule *> vrp;
            for (auto &r : vr) {
                if (r.i == SENTRY && all_fall(f.values, r))
                    vrp.push_back(&r);
            }
            if (vrp.size() == 1) {
                vrp.front()->i = f.i;
            } else {
                df.push_back(f);
            }
            df.pop_front();
        }
        return vr;
    }


    string ticket_matches_label(const vector<Rule> &rules, const string &ticket) {
        int found{0};
        string lbl;
        for (const auto &rule: rules) {
            found = 0;
            vector<string> numbers{};
            numbers = utils::split(ticket, ",");
            for (const auto &number: numbers) {
                if (stoi(number) >= rule.lb.first && stoi(number) <= rule.lb.second ||
                    stoi(number) >= rule.ub.first && stoi(number) <= rule.ub.second) {
                    found++;
                }
                if (found == numbers.size()) {
                    cout << "matches: " << rule.label << " ";
                    cout << "(" << rule.lb.first << "-" << rule.lb.second << ":" << rule.ub.first << "-"
                         << rule.ub.second << ")" << endl;
                    return rule.label;
                }
            }

        }
        return "not found";
    }

    void part2(const string &label, const string &path) {
        auto t1 = Clock::now();
        auto t_read = Clock::now();
        string r0, type, or_string, r2, ticketstring;
        vector<Ticket> valid_tickets;
        map<int, pair<vector<int>, vector<int>>> ranges;
        vector<Rule> rules{};
        std::unordered_set<int> my_ticket{11, 12, 13};

        std::fstream f{"input/16ranges2.txt"};
        while (f >> type >> r0 >> or_string >> r2) {
            string lbl{type.substr(0, type.length() - 1)};
            pair<int, int> lb, ub;
            if (!r0.empty()) {
                auto r = utils::split(r0, "-");
                lb = std::make_pair(stoi(r[0]), stoi(r[1]));
            }
            if (!r2.empty()) {
                auto r = utils::split(r2, "-");
                ub = std::make_pair(stoi(r[0]), stoi(r[1]));
            }
            rules.emplace_back(Rule{lbl, lb, ub});
        }

        std::fstream f2{"input/16tickets2.txt"};
        while (f2 >> ticketstring) {
            auto t = utils::split(ticketstring, ",");
            bool valid = true;
            for (const auto &n:t) {
                if (!valid_ticket(rules, stoi(n))) {
                    valid = false;
                }
            }
            if (valid) {
                auto vals = utils::split(ticketstring, ",");
                vector<int> nums;
                for (const auto &v:vals)
                    nums.emplace_back(stoi(v));
                valid_tickets.emplace_back(Ticket{nums});
            }
        }
        //string myticket = "191,89,73,139,71,103,109,53,97,179,59,67,79,101,113,157,61,107,181,137";
        string myticket = "11,12,13";

        cout << "----" << endl;
        for (const auto &rule:rules) {
            cout << rule.label << " (" << rule.lb.first << "-" << rule.lb.second << ":" << rule.ub.first << "-"
                 << rule.ub.second << ")" << endl;
        }
        cout << "----" << endl;
        const auto final_results = decipher_fields(rules, valid_tickets);
        Ticket t;
        auto ticket_string = utils::split(myticket, ",");
        vector<int> ticket_int;
        ticket_int.reserve(ticket_string.size());
        for (const auto &x:ticket_string)
            ticket_int.emplace_back(stoi(x));
        t.values = ticket_int;
        Index res = 1;
        for (const auto &r : final_results) {
            if (r.label.find("departure") != std::string::npos)
                res *= t.values[r.i];
        }
        cout << "done:" << res << endl;
    }

    void day16_2(const string &label, const string &path) {
        vector<string> input = utils::read_all_lines<string>(path);
        vector<pair<int, int>> validRanges;
        vector<string> fields;
        std::unordered_set<int> validNumbers;


        // Read the rules
        int i;
        for (i = 0;; i++) {
            string s = input[i];
            if (s.empty()) break;
            vector<string> split = utils::split(s, " ");
            vector<string> range2 = utils::split(split[split.size() - 1], "-");
            vector<string> range1 = utils::split(split[split.size() - 3], "-");
            fields.push_back((split.size() == 5 ? split[0] : "") + split[split.size() - 4]);
            validRanges.emplace_back(std::stoi(range1[0]), std::stoi(range1[1]));
            validRanges.emplace_back(std::stoi(range2[0]), std::stoi(range2[1]));
            for (int j = std::stoi(range2[0]); j <= std::stoi(range2[1]); j++) {
                validNumbers.insert(j);
            }
            for (int j = std::stoi(range1[0]); j <= std::stoi(range1[1]); j++) {
                validNumbers.insert(j);
            }
        }
        i += 2;

        // Read my ticket
        vector<string> myValues = utils::split(input[i], ",");
        i += 3;

        // Readnearby tickets
        int errorRate = 0;
        vector<vector<int>> validTickets(fields.size());
        for (; i < input.size(); i++) {
            string ticket = input[i];
            vector<string> strValues = utils::split(ticket, ",");
            bool valid = true;
            for (const string &x : strValues) {
                if (validNumbers.find(std::stoi(x)) == validNumbers.end()) {
                    valid = false;
                }
            }
            if (valid) {
                for (int j = 0; j < strValues.size(); j++) {
                    validTickets[j].push_back(std::stoi(strValues[j]));
                }
            }
        }


        // check which field belongs where
        vector<std::unordered_set<int>> possibleFields(fields.size()); // Stores the possible fields for each index
        pair<int, int> range1;
        pair<int, int> range2;
        bool valid;
        for (int j = 0; j < validTickets.size(); j++) {
            for (size_t k = 0; k < fields.size(); k++) {
                range1 = validRanges[k * 2];
                range2 = validRanges[k * 2 + 1];
                valid = true;
                for (int x : validTickets[j]) {
                    if (!((x >= range1.first && x <= range1.second) || (x >= range2.first && x <= range2.second))) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    possibleFields[j].insert(k);
                }
            }
        }

        std::unordered_set<int> fieldsFound;
        bool done;
        int field;
        while (true) {
            done = true;
            // Find a field with only one possibility
            for (std::unordered_set<int> f : possibleFields) {
                if (f.size() == 1 && fieldsFound.find(*f.begin()) == fieldsFound.end()) {
                    field = *f.begin();
                    done = false;
                    break;
                }
            }
            if (done) break;
            // Delete the possibility from all other fields
            for (int it = 0; it < fields.size(); it++) {
                if (possibleFields[it].size() != 1) {
                    possibleFields[it].erase(field);
                }
            }
            fieldsFound.insert(field);
        }

        unsigned long long answer = 1;
        for (int j = 0; j < fields.size(); j++) {
            for (int k : possibleFields[j]) {
                if (fields[k].substr(0, 9) == "departure") {
                    answer *= std::stoi(myValues[j]);
                }
            }
        }
        cout << answer;
    }

}

#endif //AOC_16_2_H
