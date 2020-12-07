#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>
#include "../include/split.h"

using namespace std;

namespace day7 {
    map<string, vector<string>> m_Tree;

    struct tree {
        string value;
        std::vector<tree> children;
    };

    bool hasShiny(string &key) {
        string str = "shiny gold";
        vector<string> value = m_Tree[key];
        if (key == str)
            return true;
        for (auto it : m_Tree[key]) {
            if (it == "other bags.")
                continue;
            if (it == str)
                return true;
            bool isShiny = hasShiny(it);
            if (isShiny)
                return true;
        }
        return false;
    }


    void parse_input(const string &path) {
        parse_input_by_line(path, [&](const auto &line) {
            vector<string> bags;
            split(line, ' ', bags);
            for (int i = 5; i < bags.size(); i = i + 4) {
                m_Tree[bags[0] + ' ' + bags[1]].push_back(bags[i] + " " + bags[i + 1]);
            }
        });
    };

    int solve() {
        int result =0;
        for (const auto& it : m_Tree) {
            for (auto it2 : it.second) {
                bool isShiny = hasShiny(it2);
                if (isShiny) {
                    result++;
                    break;
                }
            }
        }
        return result;
    }
}
