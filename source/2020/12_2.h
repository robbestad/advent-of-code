//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <chrono>
#include <numeric>
#include <unordered_map>
#include <cmath>
#include <type_traits>
#include "../include/utils.h"

#ifndef AOC_12_2_H
#define AOC_12_2_H
using namespace std;
namespace day12_2 {
    template<typename E>
    constexpr auto to_underlying(E e) noexcept {
        return static_cast<std::underlying_type_t<E>>(e);
    }

    using Clock = std::chrono::high_resolution_clock;

    enum dir {
        NORTH = 1, EAST = 2, SOUTH = 3, WEST = 4
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

    void turn_right(std::unordered_map<dir, int, std::hash<int> > &pos) {
        auto n = pos[dir::NORTH];
        auto w = pos[dir::WEST];
        auto s = pos[dir::SOUTH];
        auto e = pos[dir::EAST];
        pos[dir::NORTH] = w;
        pos[dir::EAST] = n;
        pos[dir::SOUTH] = e;
        pos[dir::WEST] = s;

    }

    void turn_left(std::unordered_map<dir, int, std::hash<int> > &pos) {
        auto n = pos[dir::NORTH];
        auto w = pos[dir::WEST];
        auto s = pos[dir::SOUTH];
        auto e = pos[dir::EAST];
        pos[dir::NORTH] = e;
        pos[dir::EAST] = s;
        pos[dir::SOUTH] = w;
        pos[dir::WEST] = n;
    }

    pair<size_t, size_t> part2(const vector<string> &input) {
        auto t1 = Clock::now();
        size_t result{0};

        std::unordered_map<dir, int, std::hash<int> > pos{
                {dir::NORTH, 0},
                {dir::EAST,  0},
                {dir::SOUTH, 0},
                {dir::WEST,  0}
        };

        std::unordered_map<dir, int, std::hash<int> > waypoint{
                {dir::NORTH, 1},
                {dir::EAST,  10},
                {dir::SOUTH, 0},
                {dir::WEST,  0}
        };

        auto facing = dir::EAST;

        for (auto v:input) {
            int val = stoi(utils::tail(v, v.size() - 1));
            if (v[0] == 'F') {
                for (int i = val; i > 0; i--) {
                    go_north(pos, waypoint[dir::NORTH]);
                    go_south(pos, waypoint[dir::SOUTH]);
                    go_east(pos, waypoint[dir::EAST]);
                    go_west(pos, waypoint[dir::WEST]);
                }
            }
            if (v[0] == 'N') {
                go_north(waypoint, val);
            }
            if (v[0] == 'S') {
                go_south(waypoint, val);
            }
            if (v[0] == 'W') {
                go_west(waypoint, val);
            }
            if (v[0] == 'E') {
                go_east(waypoint, val);
            }

            if (v[0] == 'R') {
                size_t degrees = val / 90;
                for (int i = 1; i <= degrees; degrees--)
                    turn_right(waypoint);

            }
            if (v[0] == 'L') {
                size_t degrees = val / 90;
                for (int i = 1; i <= degrees; degrees--)
                    turn_left(waypoint);
            }


        }
        for (auto p:pos) {
            result += p.second;
        }

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        return {result, result_time};
    }


}

#endif //AOC_12_2_H
