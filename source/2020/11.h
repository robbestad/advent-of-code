//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include "../include/utils.h"
#include <chrono>

using Clock = std::chrono::high_resolution_clock;

#ifndef AOC_11_H
#define AOC_11_H
#define DEBUG false
using namespace std;
namespace day11 {
    vector<string> strings;
    enum class Seat {
        NONE,
        FREE,
        OCCUPIED
    };


    std::ostream &operator<<(std::ostream &out, const Seat value) {
        if (value == Seat::FREE) return out << 'L';
        if (value == Seat::OCCUPIED) return out << '#';
        return out << '.';
    }

    vector<string> parse_input(const string &path) {
        vector<string> lines;
        parse_input_by_line(path, [&](const auto &line) {
            lines.emplace_back(line);
        });
        return lines;
    };

    vector<vector<Seat>> to_seats(const vector<string> &input) {
        vector<vector<Seat>> seats = {};

        for (auto &row : input) {
            seats.emplace_back();
            for (auto &seat : row) {
                if (seat == 'L')
                    seats[seats.size() - 1].push_back(Seat::FREE);
                else
                    seats[seats.size() - 1].push_back(Seat::NONE);
            }
        }
        return seats;
    }

    pair<vector<vector<Seat>>, bool> FindSeats(
            const vector<vector<Seat>> &seats,
            int maxTaken,
            const function<int(const vector<vector<Seat>> &,
                               int, int)> &countMethod) {
        vector<vector<Seat>> newSeats = seats;
        bool changed = false;
        for (int x = 0; x < seats.size(); x++) {
            for (int y = 0; y < seats[x].size(); y++) {
                if (seats[x][y] != Seat::NONE) {
                    int taken = countMethod(seats, x, y);
                    if (taken == 0) {
                        newSeats[x][y] = Seat::OCCUPIED;
                        changed = changed ? changed : seats[x][y] != newSeats[x][y];
                    } else if (taken >= maxTaken) {
                        newSeats[x][y] = Seat::FREE;
                        changed = changed ? changed : seats[x][y] != newSeats[x][y];
                    }
                }
            }
        }
        return {newSeats, changed};
    }


    int seat_visible(const vector<vector<Seat>> &seats, int vertical_pos, int horizontal_pos,
                     const int vertical_delta, const int horizontal_delta) {
        vertical_pos += vertical_delta;
        horizontal_pos += horizontal_delta;
        while (vertical_pos >= 0 && vertical_pos < seats.size() &&
               horizontal_pos >= 0 && horizontal_pos < seats[vertical_pos].size()) {
            if (seats[vertical_pos][horizontal_pos] == Seat::OCCUPIED) return 1;
            if (seats[vertical_pos][horizontal_pos] == Seat::FREE) return 0;
            vertical_pos += vertical_delta;
            horizontal_pos += horizontal_delta;
        }
        return 0;
    }

    int count_adjacent_3(const vector<vector<Seat>> &seats, int row, int col) {
        return seat_visible(seats, row, col, -1, -1) +
               seat_visible(seats, row, col, -1, 0) +
               seat_visible(seats, row, col, -1, 1) +
               seat_visible(seats, row, col, 0, -1) +
               seat_visible(seats, row, col, 0, 1) +
               seat_visible(seats, row, col, 1, -1) +
               seat_visible(seats, row, col, 1, 0) +
               seat_visible(seats, row, col, 1, 1);
    }


    int count_adjacent_2(const vector<vector<Seat>> &seats, int row, int col) {
        size_t count = 0;
        static const vector<pair<int, int>> dirs = {
                {1,  0},
                {1,  1},
                {0,  1},
                {-1, 1},
                {-1, 0},
                {-1, -1},
                {0,  -1},
                {1,  -1}
        };

        for (const auto &[dx, dy] : dirs) {
            int x = row + dx;
            int y = col + dy;
            while (x >= 0 && x < seats.size() && y >= 0 && y < seats.front().size()) {
                if (seats[x][y] == Seat::OCCUPIED) {
                    count++;
                    break;
                } else if (seats[x][y] == Seat::FREE) {
                    break;
                }
                x += dx;
                y += dy;
            }
        }
        return count;
    }

    int count_adjacent(const vector<vector<Seat>> &seats, int row, int col) {
        int count = 0;
        if (row > 0) {
            if (col > 0) {
                count += (seats[row - 1][col - 1] == Seat::OCCUPIED);
            }
            count += (seats[row - 1][col] == Seat::OCCUPIED);
            if (col < seats[row - 1].size() - 1) {
                count += (seats[row - 1][col + 1] == Seat::OCCUPIED);
            }
        }

        if (col > 0) {
            count += (seats[row][col - 1] == Seat::OCCUPIED);
        }
        if (col < seats[row].size() - 1) {
            count += (seats[row][col + 1] == Seat::OCCUPIED);
        }

        if (row < seats.size() - 1) {
            if (col > 0) {
                count += (seats[row + 1][col - 1] == Seat::OCCUPIED);
            }
            count += (seats[row + 1][col] == Seat::OCCUPIED);
            if (col < seats[row + 1].size() - 1) {
                count += (seats[row + 1][col + 1] == Seat::OCCUPIED);
            }
        }

        return count;
    }

    pair<size_t,size_t> part1(const vector<string> &input) {
        auto t1 = Clock::now();
        vector<vector<Seat>> seats = to_seats(input);
        int count = 0;
        int maxTaken = 4;
        map<size_t, vector<vector<Seat>>> moves;
        moves.emplace(pair(0, seats));

        bool changed = true;
        while (changed) {
            auto[newSeats, newChanged] = FindSeats(seats, maxTaken, count_adjacent);
            seats = move(newSeats);
            changed = newChanged;
            moves.emplace(pair(++count, seats));
        }

#if DEBUG
        for (const auto &m:moves) {
            cout << endl << "Runde " << m.first + 1 << endl;
            for (const auto &row:m.second) {
                for (const auto &col:row) {
                    cout << col;
                }
                cout << endl;
            }
        }
#endif
        size_t occupied_rows{0};

        vector<vector<Seat>> lastMove = moves[moves.size() - 1];
        for (const auto &row : lastMove) {
            for (const auto &seat : row) {
                if (seat == Seat::OCCUPIED) { occupied_rows++; }
            }
        }
        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        return {occupied_rows,result_time};
    }

    pair<size_t,size_t> part2(const vector<string> &input) {
        auto t1 = Clock::now();
        vector<vector<Seat>> seats = to_seats(input);
        int count = 0;
        int max_occupied = 5;
        map<size_t, vector<vector<Seat>>> moves;
        moves.emplace(pair(0, seats));

        bool changed = true;
        while (changed) {
            auto[new_seats, has_changed] = FindSeats(seats, max_occupied, count_adjacent_2);
            seats = move(new_seats);
            changed = has_changed;
            moves.emplace(pair(++count, seats));
            //if (count > 2) break;
        }

#if DEBUG
        for (const auto &m:moves) {
            cout << endl << "Runde " << m.first + 1 << endl;
            for (const auto &row:m.second) {
                for (const auto &col:row) {
                    cout << col;
                }
                cout << endl;
            }
        }
#endif
        size_t occupied_rows{0};

        vector<vector<Seat>> last_move = moves[moves.size() - 1];
        for (const auto &row : last_move) {
            for (const auto &seat : row) {
                if (seat == Seat::OCCUPIED) { occupied_rows++; }
            }
        }

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        return {occupied_rows,result_time};
    }

}

#endif //AOC_11_H
