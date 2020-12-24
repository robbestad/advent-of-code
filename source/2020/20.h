//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include <chrono>
#include "../include/utils.h"

#ifndef AOC_20_H
#define AOC_20_H
using namespace std;
namespace day20 {
    using std::string;
    using std::vector;
    using std::unordered_set;
    using std::cout;
    using std::endl;
    using std::array;
    using std::unordered_map;
    using chrono::duration_cast;
    using chrono::milliseconds;
    using tile_t = std::vector<std::string>;
    using ll = int64_t;
    using input_t = std::unordered_map<ll, tile_t>;
    using result_t = ll;

    struct border_inverse_t {
        ll border;
        ll tile_id;
        ll type;
    };

    array<int, 10> get_border(const tile_t &tile) {
        assert(tile.size() == tile.front().size());
        //tiles_border_t borders{ 0, 0, 0, 0, 0, 0, 0, 0 };
        array<int, 10> border{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (size_t i = 0; i < tile.size(); i++) {
            if (tile[i] == "#") border[i] = 1;
        }
        return border;
    }

    result_t solve1(input_t const &input_data) {
        std::vector<border_inverse_t> border_inv_info;
        for (auto const &t : input_data) {
            auto const border = get_border(t.second);
            //border_inv_info.emplace_back(border);
        }
        return 0;
    }

    void part2(const vector<string> &input) {
    }

    input_t
    read_input(std::ifstream &file) {
        std::string line{};
        tile_t tile;
        input_t input_values;
        while (std::getline(file, line)) {
            if (line.empty()) {
                break;
            }

            auto const idx = line.find("Tile ");
            assert(idx == 0);
            auto const id = std::stoi(line.substr(5));

            tile.clear();
            while (std::getline(file, line)) {
                if (line.empty()) {
                    break;
                }
                tile.emplace_back(line);
            }
            input_values.emplace(id, tile);
        }
        return input_values;
    }

    void start(const string &label, const string &path) {
        std::ifstream input_file(path);
        auto begin_input = std::chrono::steady_clock::now();
        auto og_tiles = read_input(input_file);
        auto end_input = std::chrono::steady_clock::now();
        std::cout << "Read Input Time = "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end_input - begin_input).count() << "[ms]"
                  << std::endl;

        auto begin_s1 = std::chrono::steady_clock::now();
        auto const s1 = solve1(og_tiles);
        auto end_s1 = std::chrono::steady_clock::now();
        std::cout << "Solution Part1: " << s1
                  << "   -> Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_s1 - begin_s1).count()
                  << "[ms]" << std::endl;


        for (auto &x:og_tiles) {
            cout << x.first << endl;
            for (auto &y:x.second)
                cout << y << endl;
        }


    }

}

#endif //AOC_20_H
