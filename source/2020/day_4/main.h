#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include "../day_2/split.hpp"

using namespace std;
namespace day4 {

    int parse(const vector<string> &passports) {
        int it = 0;
        int valid = 0;
        do {
            auto fields = split(passports.at(it), " ");

            int checks = 0;
            for (auto const &v:fields) {
                if (v.starts_with("ecl"))
                    checks++;
                if (v.starts_with("byr"))
                    checks++;
                if (v.starts_with("pid"))
                    checks++;
                if (v.starts_with("eyr"))
                    checks++;
                if (v.starts_with("hcl"))
                    checks++;
                if (v.starts_with("iyr"))
                    checks++;
                if (v.starts_with("hgt"))
                    checks++;
            }

            if (checks == 7)
                valid++;

        } while (++it < passports.size());
        return valid;
    }

    int parseStrict(const vector<string> &passports) {
        int it = 0;
        int valid = 0;
        do {
            auto fields = split(passports.at(it), " ");

            int checks = 0;
            for (auto const &v:fields) {
                if (v.starts_with("ecl")) {
                    auto ecl = split(v, ":");
                    if (ecl[1] == "amb" ||
                        ecl[1] == "blu" ||
                        ecl[1] == "brn" ||
                        ecl[1] == "gry" ||
                        ecl[1] == "grn" ||
                        ecl[1] == "hzl" ||
                        ecl[1] == "oth")
                        checks++;
                }
                if (v.starts_with("byr")) {
                    //1920 - 2002
                    auto byr = split(v, ":");
                    if (stoi(byr[1]) > 1919 && stoi(byr[1]) < 2003)
                        checks++;
                }
                if (v.starts_with("pid")) {
                    auto pid = split(v, ":");
                    if (pid[1].length() == 9)
                        checks++;
                }
                if (v.starts_with("eyr")) {
                    auto eyr = split(v, ":");
                    if (stoi(eyr[1]) >= 2020 && stoi(eyr[1]) <= 2030)
                        checks++;
                }
                if (v.starts_with("hcl")) {
                    auto hcl = split(v, ":");
                    if (hcl[1].starts_with("#")) {
                        if (regex_match(hcl[1], regex("^#([a-f0-9]{6})$")))
                            checks++;
                    }
                }
                if (v.starts_with("iyr")) {
                    auto iyr = split(v, ":");
                    if (stoi(iyr[1]) >= 2010 && stoi(iyr[1]) <= 2020)
                        checks++;
                }
                if (v.starts_with("hgt")) {
                    auto hgt = split(v, ":");
                    if (hgt[1].ends_with("in")) {
                        auto h = split(hgt[1], "in");
                        if (stoi(h[0]) >= 59 && stoi(h[0]) <= 76)
                            checks++;
                    }
                    if (hgt[1].ends_with("cm")) {
                        auto h = split(hgt[1], "cm");
                        if (stoi(h[0]) >= 150 && stoi(h[0]) <= 193)
                            checks++;
                    }
                }
            }

            if (checks == 7)
                valid++;

        } while (++it < passports.size());
        return valid;
    }


    vector<string> lesFil(string const &fil) {
        ifstream inFile;

        inFile.open(fil);
        vector<string> map;
        if (inFile.fail()) {
            cerr << "Fil kunne ikke åpnes" << endl;
            inFile.close();
            exit(1);
        }

        string row;
        string temp;
        int num = 0;
        while (getline(inFile, row)) {
            num++;
            temp += row + " ";
            if (row.empty()) {
                //cout << temp << endl;
                map.push_back(temp);
                temp = "";
            }
        }
        map.push_back(temp);
        inFile.close();
        return map;
    }

    int part1() {
        vector<string> passports = lesFil("source/day_4/input");
        int part1 = parse(passports);
        return part1;
    }
    int part2() {
        vector<string> passports = lesFil("source/day_4/input");
        int part2 = parseStrict(passports);
        return part2;
    }
}

