//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <numeric>
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
  //      if(player1.empty() || player2.empty())
//            cout << "winner?";
        //assert(p1 > 0);
        //assert(p2 > 0);
        auto winner = p1 > p2 ? 1 : p2 > p1 ? 2 : 0;
        player1.pop_front();
        player2.pop_front();

        if (winner == 1) {
            //cout << "Round " << round << "\t\tPlayer 1 wins the round!" << endl;
            player1.push_back(p1);
            player1.push_back(p2);
        } else if (winner == 2) {
            //cout << "Round " << round << "\t\tPlayer 2 wins the round!" << endl;
            player2.push_back(p2);
            player2.push_back(p1);
        } else if (winner == 0) {
            //player2.push_back(p2);
            //player1.push_back(p1);
            //cout << "***TIE" << endl;
        }
        round += 1;
    }

    unsigned long count_score(deque<size_t> &cards) {
        unsigned long score{0};
        unsigned long idx{0};
        while (!cards.empty()) {
            size_t card = cards.back();
            cards.pop_back();
            score += ++idx * card;
        }
        return score;
    }

    void start(const string &lbl, const string &path) {
        deque<size_t> player1, player2;
        std::ifstream input_file(path);
        read_input(input_file, player1, player2);
        size_t round{0};
        do {
            play(round, player1, player2);
            if(player1.empty())
                break;
            if(player2.empty())
                break;
        } while (true);

        unsigned long score{0};
        if (!player1.empty())
            score = count_score(player1);
        else
            score = count_score(player2);
        cout << score << endl;
    }

}

#endif //AOC_22_H
