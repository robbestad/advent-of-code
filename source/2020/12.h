//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <numeric>
#include <chrono>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <type_traits>
#include "../include/utils.h"

#ifndef AOC_12_H
#define AOC_12_H
using namespace std;
namespace day12 {
    template<typename E>
    constexpr auto to_underlying(E e) noexcept {
        return static_cast<std::underlying_type_t<E>>(e);
    }

    using Clock = std::chrono::high_resolution_clock;

    enum dir {
        NORTH = (int) 1, EAST = (int) 2, SOUTH = (int) 3, WEST = (int) 4
    };

    std::ostream &operator<<(std::ostream &out, const dir value) {
        if (value == dir::NORTH) return out << 'N';
        if (value == dir::SOUTH) return out << 'S';
        if (value == dir::EAST) return out << utils::unicode_to_utf8(0x00D8);
        if (value == dir::WEST) return out << 'V';
        return out << '.';
    }

    void go_north(std::unordered_map<dir, int, std::hash<int> > &pos, int val) {
        pos[dir::SOUTH] -= val;
        if (pos[dir::SOUTH] < 0) {
            pos[dir::NORTH] += abs(pos[dir::SOUTH]);
            pos[dir::SOUTH] = 0;
        }
    }

    void go_south(std::unordered_map<dir, int, std::hash<int> > &pos, int val) {
        pos[dir::NORTH] -= val;
        if (pos[dir::NORTH] < 0) {
            pos[dir::SOUTH] += abs(pos[dir::NORTH]);
            pos[dir::NORTH] = 0;
        }
    }

    void go_west(std::unordered_map<dir, int, std::hash<int> > &pos, int val) {
        pos[dir::EAST] -= val;
        if (pos[dir::EAST] < 0) {
            pos[dir::WEST] += abs(pos[dir::EAST]);
            pos[dir::EAST] = 0;
        }
    }

    void go_east(std::unordered_map<dir, int, std::hash<int> > &pos, int val) {
        pos[dir::WEST] -= val;
        if (pos[dir::WEST] < 0) {
            pos[dir::EAST] += abs(pos[dir::WEST]);
            pos[dir::WEST] = 0;
        }
    }

    void turn_right(std::unordered_map<dir, int, std::hash<int> > &pos, dir &facing, int degrees) {
        auto start = to_underlying(facing);
        if (start == 4) start = 0;
        auto turn = start + degrees;
        facing = dir(turn);
    }

    void turn_left(std::unordered_map<dir, int, std::hash<int> > &pos, dir &facing, int degrees) {
        int start = (int) to_underlying(facing);
        if (start == 0) start = 4;
        auto turn = start - degrees;
        if (turn == 0) turn = 4;
        facing = dir(turn);
    }

    pair<size_t, size_t> part1(const vector<string> &input) {
        auto t1 = Clock::now();
        size_t result{0};

        std::unordered_map<dir, int, std::hash<int> > pos{
                {dir::NORTH, 0},
                {dir::EAST,  0},
                {dir::SOUTH, 0},
                {dir::WEST,  0}
        };

        auto facing = dir::EAST;

        for (auto v:input) {
            int val = stoi(utils::tail(v, v.size() - 1));
            if (v[0] == 'F') {
                if (facing == dir::NORTH) {
                    go_north(pos, val);
                }
                if (facing == dir::SOUTH) {
                    go_south(pos, val);
                }
                if (facing == dir::WEST) {
                    go_west(pos, val);
                }
                if (facing == dir::EAST) {
                    go_east(pos, val);
                }
            }
            if (v[0] == 'N') {
                go_north(pos, val);
            }
            if (v[0] == 'S') {
                go_south(pos, val);
            }
            if (v[0] == 'W') {
                go_west(pos, val);
            }
            if (v[0] == 'E') {
                go_east(pos, val);
            }

            if (v[0] == 'R') {
                size_t degrees = val / 90;
                for (int i = 1; i <= degrees; degrees--)
                    turn_right(pos, facing, i);

            }
            if (v[0] == 'L') {
                size_t degrees = val / 90;
                for (int i = 1; i <= degrees; degrees--)
                    turn_left(pos, facing, i);
            }
            // cout << "N:" << pos[dir::NORTH] << " E:" << pos[dir::EAST] << " S:" << pos[dir::SOUTH] << " W:"
            //    << pos[dir::WEST] << endl;
        }
        for (auto p:pos) {
           // cout << p.first << ":" << p.second << endl;
            result += p.second;
        }

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        return {result, result_time};
    }


}

#endif //AOC_12_H
