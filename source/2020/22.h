//
// Created by Sven Anders Robbestad on 08/12/2020.

#include <numeric>
#include <algorithm>
#include <numeric>
#include <set>
#include <unordered_set>
#include <deque>
#include "../include/utils.h"

#ifndef AOC_22_H
#define AOC_22_H
namespace day22 {
    using std::deque;
    using Clock = std::chrono::high_resolution_clock;

    void read_input(std::ifstream &file, deque<size_t> &player1, deque<size_t> &player2) {
        std::string line{};
        while (std::getline(file, line)) {
            if (line.empty()) {
                break;
            }
            auto const idx = line.find("Player 1:");
            assert(idx == 0);
            while (std::getline(file, line)) {
                if (line.empty()) {
                    break;
                }
                if (line.starts_with("Player")) {
                    continue;
                }
                player1.push_back(stoi(line));
            }

            auto const idx2 = line.find("Player 2:");
            while (std::getline(file, line)) {
                if (line.empty()) {
                    break;
                }
                if (line.starts_with("Player")) {
                    continue;
                }
                player2.push_back(stoi(line));
            }
        }
    }

    void play(size_t &round, deque<size_t> &player1, deque<size_t> &player2) {
        auto p1 = player1.front();
        auto p2 = player2.front();
        auto winner = p1 > p2 ? 1 : p2 > p1 ? 2 : 0;
        player1.pop_front();
        player2.pop_front();

        if (winner == 1) {
            player1.push_back(p1);
            player1.push_back(p2);
        } else if (winner == 2) {
            player2.push_back(p2);
            player2.push_back(p1);
        }
        round += 1;
    }

    unsigned long score(std::deque<size_t> &cards) {
        unsigned long score{0};
        unsigned long idx{0};
        while (!cards.empty()) {
            size_t card = cards.back();
            cards.pop_back();
            score += ++idx * card;
        }
        return score;
    }

    std::deque<size_t> deque_copy(int top, const std::deque<size_t> &qu) {
        std::deque<size_t> copy{};
        for (size_t i = 0; i < top; i++) {
            copy.push_back(qu.at(i));
        }
        return copy;
    }

    std::pair<size_t, long> play_recursive(std::deque<size_t> &player1, std::deque<size_t> &player2) {
        std::set<std::pair<std::deque<size_t>, std::deque<size_t>>> prev_decks;

        while (!player1.empty() && !player2.empty()) {
            if (prev_decks.contains({player1, player2})) {
                return {1, score(player1)};
            }
            prev_decks.insert({player1, player2});

            auto p1 = player1.front();
            auto p2 = player2.front();
            player1.pop_front();
            player2.pop_front();

            size_t winner;

            if (p1 <= player1.size() && p2 <= player2.size()) {
                std::deque<size_t> p1_copy = deque_copy(p1, player1);
                std::deque<size_t> p2_copy = deque_copy(p2, player2);

                const auto&[winning_player, _] = play_recursive(p1_copy, p2_copy);
                winner = winning_player;
            } else {
                winner = p1 > p2 ? 1 : 2;
            }

            if (winner == 1) {
                player1.push_back(p1);
                player1.push_back(p2);
            } else if (winner == 2) {
                player2.push_back(p2);
                player2.push_back(p1);
            }
        }

        if (!player1.empty()) {
            return {1, score(player1)};
        } else {
            return {2, score(player2)};
        }
    }

    long part_two(std::deque<size_t> &player_1_deck, std::deque<size_t> player_2_deck) {
        const auto&[_, winning_score] = play_recursive(player_1_deck, player_2_deck);
        return winning_score;
    }

    void play1(const string &lbl, const string &path) {
        deque<size_t> player1, player2;
        std::ifstream input_file(path);
        read_input(input_file, player1, player2);
        auto begin_s1 = std::chrono::steady_clock::now();
        size_t round{0};
        do {
            play(round, player1, player2);
            if (player1.empty())
                break;
            if (player2.empty())
                break;
        } while (true);

        unsigned long sum{0};
        if (!player1.empty())
            sum = score(player1);
        else
            sum = score(player2);
        auto end_s1 = std::chrono::steady_clock::now();
        std::cout << endl << "Løsning del 1: " << sum
                  << "   -> Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_s1 - begin_s1).count()
                  << "[us]" << std::endl;
    }

    void play2(const string &lbl, const string &path) {
        deque<size_t> player1, player2;
        std::ifstream input_file(path);
        read_input(input_file, player1, player2);
        auto begin_s1 = std::chrono::steady_clock::now();
        auto count = part_two(player1, player2);
        auto end_s1 = std::chrono::steady_clock::now();
        std::cout << endl << "Løsning del 2: " << count
                  << "   -> Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_s1 - begin_s1).count()
                  << "[ms]" << std::endl;

    }

}

#endif //AOC_22_H
