//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <array>
#include <unordered_set>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include "../include/utils.h"

constexpr static std::array<glm::ivec3, 26> offsets3 =
        {{
                 {-1, -1, -1},
                 {-1, -1, 0},
                 {-1, -1, +1},
                 {-1, 0, -1},
                 {-1, 0, 0},
                 {-1, 0, +1},
                 {-1, +1, -1},
                 {-1, +1, 0},
                 {-1, +1, +1},
                 {0, -1, -1},
                 {0, -1, 0},
                 {0, -1, +1},
                 {0, 0, -1},
                 {0, 0, +1},
                 {0, +1, -1},
                 {0, +1, 0},
                 {0, +1, +1},
                 {+1, -1, -1},
                 {+1, -1, 0},
                 {+1, -1, +1},
                 {+1, 0, -1},
                 {+1, 0, 0},
                 {+1, 0, +1},
                 {+1, +1, -1},
                 {+1, +1, 0},
                 {+1, +1, +1},
         }};

constexpr static std::array<glm::ivec4, 80> offsets4 =
        {{
                 {-1, -1, -1, -1},
                 {-1, -1, -1, +0},
                 {-1, -1, -1, +1},
                 {-1, -1, +0, -1},
                 {-1, -1, +0, +0},
                 {-1, -1, +0, +1},
                 {-1, -1, +1, -1},
                 {-1, -1, +1, +0},
                 {-1, -1, +1, +1},
                 {-1, +0, -1, -1},
                 {-1, +0, -1, +0},
                 {-1, +0, -1, +1},
                 {-1, +0, +0, -1},
                 {-1, +0, +0, +0},
                 {-1, +0, +0, +1},
                 {-1, +0, +1, -1},
                 {-1, +0, +1, +0},
                 {-1, +0, +1, +1},
                 {-1, +1, -1, -1},
                 {-1, +1, -1, +0},
                 {-1, +1, -1, +1},
                 {-1, +1, +0, -1},
                 {-1, +1, +0, +0},
                 {-1, +1, +0, +1},
                 {-1, +1, +1, -1},
                 {-1, +1, +1, +0},
                 {-1, +1, +1, +1},
                 {+0, -1, -1, -1},
                 {+0, -1, -1, +0},
                 {+0, -1, -1, +1},
                 {+0, -1, +0, -1},
                 {+0, -1, +0, +0},
                 {+0, -1, +0, +1},
                 {+0, -1, +1, -1},
                 {+0, -1, +1, +0},
                 {+0, -1, +1, +1},
                 {+0, +0, -1, -1},
                 {+0, +0, -1, +0},
                 {+0, +0, -1, +1},
                 {+0, +0, +0, -1},
                 {+0, +0, +0, +1},
                 {+0, +0, +1, -1},
                 {+0, +0, +1, +0},
                 {+0, +0, +1, +1},
                 {+0, +1, -1, -1},
                 {+0, +1, -1, +0},
                 {+0, +1, -1, +1},
                 {+0, +1, +0, -1},
                 {+0, +1, +0, +0},
                 {+0, +1, +0, +1},
                 {+0, +1, +1, -1},
                 {+0, +1, +1, +0},
                 {+0, +1, +1, +1},
                 {+1, -1, -1, -1},
                 {+1, -1, -1, +0},
                 {+1, -1, -1, +1},
                 {+1, -1, +0, -1},
                 {+1, -1, +0, +0},
                 {+1, -1, +0, +1},
                 {+1, -1, +1, -1},
                 {+1, -1, +1, +0},
                 {+1, -1, +1, +1},
                 {+1, +0, -1, -1},
                 {+1, +0, -1, +0},
                 {+1, +0, -1, +1},
                 {+1, +0, +0, -1},
                 {+1, +0, +0, +0},
                 {+1, +0, +0, +1},
                 {+1, +0, +1, -1},
                 {+1, +0, +1, +0},
                 {+1, +0, +1, +1},
                 {+1, +1, -1, -1},
                 {+1, +1, -1, +0},
                 {+1, +1, -1, +1},
                 {+1, +1, +0, -1},
                 {+1, +1, +0, +0},
                 {+1, +1, +0, +1},
                 {+1, +1, +1, -1},
                 {+1, +1, +1, +0},
                 {+1, +1, +1, +1},
         }};


#ifndef AOC_17_H
#define AOC_17_H
using std::string;
using std::unordered_set;
using std::unordered_map;
using std::size_t;
using std::uintmax_t;


namespace day17 {
    using Clock = std::chrono::high_resolution_clock;

    size_t part1(const unordered_set<glm::ivec3> &start_cubes, size_t cycles) {
        std::unordered_set<glm::ivec3> cubes = start_cubes;

        for (std::size_t cycle = 0; cycle < cycles; ++cycle) {
            std::unordered_map<glm::ivec3, std::uintmax_t> sum_of_fields;
            for (const auto &cube : cubes) {
                for (const auto &offset : offsets3) {
                    ++sum_of_fields[glm::ivec3(cube) + offset];
                }
            }
            unordered_set<glm::ivec3> NextField;
            for (const auto &Sum : sum_of_fields) {
                if (Sum.second == 2 && cubes.count(glm::vec4(Sum.first, 1)))
                    NextField.insert(glm::ivec4(Sum.first, 1));
                if (Sum.second == 3)
                    NextField.insert(glm::ivec4(Sum.first, 1));
            }
            cubes = NextField;
        }
        return cubes.size();
    }

    size_t part2(const unordered_set<glm::ivec4> &start_cubes, size_t cycles) {
        unordered_set<glm::ivec4> cubes = start_cubes;

        for (size_t cycle = 0; cycle < cycles; ++cycle) {
            unordered_map<glm::ivec4, uintmax_t> sum_of_fields;
            for (const auto &cube : cubes) {
                for (const auto &offset : offsets4) {
                    ++sum_of_fields[(cube + offset)];
                }
            }
            unordered_set<glm::ivec4> NextField;
            for (const auto &Sum : sum_of_fields) {
                if (Sum.second == 2 && cubes.count(Sum.first))
                    NextField.insert(Sum.first);
                if (Sum.second == 3 && cubes.count(Sum.first))
                    NextField.insert(Sum.first);
            }
            cubes = NextField;
        }
        return cubes.size();
    }

    void start(const string &label, const string &path) {
        auto t1 = Clock::now();
        size_t result{0};
        std::fstream f{path};
        unordered_set<glm::ivec3> cubes;
        string x;
        size_t row = 0;
        while (f >> x) {
            {
                for (size_t y = 0; y < x.size(); ++y) {
                    if (x[y] == '#') cubes.insert({y, row, 0});
                }
                ++row;
            }
        }
        result = part1(cubes, 6);
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        cout << endl << label << ": "
             << result
             << " (compute: "
             << result_time << " us)"
             << endl;

        t1 = Clock::now();
        //result = part2(cubes, 6);
        result_time = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        cout << endl << label << ": "
             << result
             << " (compute: "
             << result_time << " us)"
             << endl;
    }


}

#endif //AOC_17_H
