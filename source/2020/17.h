//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <array>
#include <unordered_set>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include "../include/Math.h"
#include "../include/utils.h"
#include "../include/offsets.h"

#ifndef AOC_17_H
#define AOC_17_H
using std::string;
using std::unordered_set;
using std::unordered_map;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

namespace day17 {
    using Clock = std::chrono::high_resolution_clock;

    size_t part1(const unordered_set<glm::ivec3> &start_cubes, size_t cycles) {
        unordered_set<glm::ivec3> cubes = start_cubes;

        for (size_t cycle = 0; cycle < cycles; ++cycle) {
            unordered_map<glm::ivec3, size_t> sum_cubes;
            for (const auto &cube : cubes) {
                for (const auto &offset : offsets3) {
                    ++sum_cubes[glm::ivec3(cube) + offset];
                }
            }
            unordered_set<glm::ivec3> next_cube;
            for (const auto &sum : sum_cubes) {
                if (sum.second == 2 && cubes.count(glm::vec4(sum.first, 1)))
                    next_cube.insert(glm::ivec4(sum.first, 1));
                if (sum.second == 3)
                    next_cube.insert(glm::ivec4(sum.first, 1));
            }
            cubes = next_cube;
        }
        return cubes.size();
    }


    size_t part2(const unordered_set<glm::ivec4> &start_cubes, size_t cycles) {
        unordered_set<glm::ivec4> cubes = start_cubes;

        for (size_t cycle = 0; cycle < cycles; ++cycle) {
            unordered_map<glm::ivec4, size_t> sum_cubes;
            for (const auto &cube : cubes) {
                for (const auto &offset : offsets4) {
                    ++sum_cubes[glm::ivec4(cube) + offset];
                }
            }
            unordered_set<glm::ivec4> next_cube;
            for (const auto &sum : sum_cubes) {
                if (sum.second == 2 && cubes.count(glm::vec4(sum.first)))
                    next_cube.insert(glm::ivec4(sum.first));
                if (sum.second == 3)
                    next_cube.insert(glm::ivec4(sum.first));
            }
            cubes = next_cube;
        }
        return cubes.size();
    }

    uintmax_t part_2(const unordered_set<glm::ivec4> &start_cubes, size_t cycles) {
        unordered_set<glm::ivec4> cubes = start_cubes;
        for (size_t i = 0; i < cycles; i++) {
            unordered_map<glm::ivec4, long> sum_cubes;
            for (const auto &cube : cubes) {
                for (const auto &offset : offsets4) ++sum_cubes[cube + offset];
            }
            unordered_set<glm::ivec4> next_cube;
            for (const auto &sum : sum_cubes) {
                if (sum.second == 2 && cubes.count(sum.first))
                    next_cube.insert(sum.first);
                if (sum.second == 3 && !cubes.count(sum.first))
                    next_cube.insert(sum.first);
            }
            cubes = next_cube;
        }
        return cubes.size();
    }

    void start(const string &label, const string &path) {
        std::fstream f{path};
        unordered_set<glm::ivec3> cubes;
        unordered_set<glm::ivec4> cubes4;
        string x;
        size_t row = 0;
        while (f >> x) {
            {
                for (size_t y = 0; y < x.size(); ++y) {
                    if (x[y] == '#') cubes.insert({y, row, 0});
                    if (x[y] == '#') cubes4.insert({y, row, 0, 0});
                }
                row++;
            }
        }
        auto t1 = Clock::now();
        cout << endl << label << ": "
             << part1(cubes, 6)
             << " (compute: "
             << duration_cast<milliseconds>(Clock::now() - t1).count() << " us)"
             << endl;


        t1 = Clock::now();
        cout << endl << label << ": "
             << part2(cubes4, 6)
             << " (compute: "
             << duration_cast<milliseconds>(Clock::now() - t1).count() << " us)"
             << endl;
    }


}

#endif //AOC_17_H
