//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include "../include/common.h"
#include "../include/utils.h"
#include "./matvare.h"
#include <algorithm>

#ifndef AOC_21_H
#define AOC_21_H
namespace day21 {
    using ingredient_t = std::vector<std::string>;
    using allergen_t = std::vector<std::string>;
    using ll = int64_t;
    using input_t = std::unordered_map<ll, ingredient_t>;

    std::vector<Matvare *>
    read_input(std::ifstream &file, vector<Matvare *> &ingredients_list) {
        std::string line{};
        int index = -1;
        while (std::getline(file, line)) {
            if (line.empty()) {
                break;
            }
            auto fixed_line = regex_replace(line, (regex) "contains ", "");
            fixed_line = regex_replace(fixed_line, (regex) " ", ",");
            fixed_line = regex_replace(fixed_line, (regex) ",,", ",");
            auto input = utils::split(fixed_line, "(");
            std::string ingredients = input[0].substr(0, (input[0].length() - 1));
            std::string allergens = input[1].substr(0, (input[1].length() - 1));
            auto ingredient1 = new Matvare(++index, ingredients, allergens);
            ingredients_list.push_back(ingredient1);
        }
        return ingredients_list;
    }


    void start(const string &label, const string &path) {
        std::ifstream input_file(path);
        auto begin_s1 = std::chrono::steady_clock::now();

        vector<Matvare *> matvarer;
        read_input(input_file, matvarer);
        /*
        cout << "-----" << endl;
        for (const auto &i:matvarer) {
            cout << i->ingredienser << ":";
            cout << i->mulige_allergener;
            cout << endl;
        }
        cout << "-----" << endl;
        */

        std::vector<std::string> alle_ingredienser;
        for (const auto &m:matvarer) {
            auto ingredienser = utils::split(m->ingredienser, ",");
            for (const auto &i:ingredienser) {
                alle_ingredienser.emplace_back(i);
            }
        }

        std::unordered_map<std::string, std::unordered_set<std::string>> imapset;
        for (const auto &m:matvarer) {
            auto ingredienser = utils::split(m->ingredienser, ",");
            auto allergener = utils::split(m->mulige_allergener, ",");

            for (const auto &a: allergener) {
                //cout << a << "-" << m->ingredienser << endl;
                if (imapset.find(a) != imapset.end()) {
                    auto prev_set = imapset[a];
                    auto i_vec = utils::split(m->ingredienser, ",");
                    sort(i_vec.begin(), i_vec.end());
                    auto it = std::set_intersection(prev_set.begin(), prev_set.end(), i_vec.begin(), i_vec.end(),
                                                    i_vec.begin());
                    i_vec.resize(it - i_vec.begin());
                    std::unordered_set<std::string> i_set;
                    for (const auto &v:i_vec) {
                        i_set.insert(v);
                    }
                    imapset.erase(a);
                    imapset.emplace(a, i_set);

                } else {
                    auto i_vec = utils::split(m->ingredienser, ",");
                    sort(i_vec.begin(), i_vec.end());
                    std::unordered_set<std::string> i_set;
                    for (const auto &v:i_vec) {
                        i_set.insert(v);
                    }

                    imapset.emplace(a, i_set);
                }
            }

        }

        size_t count{0};
        for (const auto &a:alle_ingredienser) {
            bool print = true;
            for (const auto &x:imapset)
                for (const auto &p: x.second) {
                    if (a == p)
                        print = false;
                }
            if (print) {
                count++;
                if(count%10==1) cout << endl;
                cout << " *" << a << "* ";
            }
        }

        auto end_s1 = std::chrono::steady_clock::now();
        std::cout << endl << "Løsning del 1: " << count
                  << "   -> Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_s1 - begin_s1).count()
                  << "[ms]" << std::endl;

    }

}

#endif //AOC_21_H
