//
// Created by Sven Anders Robbestad on 21/12/2020.
//

#include <utility>

#include "../include/common.h"

#ifndef MATVARE_H
#define MATVARE_H

class Matvare {
public:
    Matvare() {
        index = -1;
    }

    explicit Matvare(int num, const string &ingredienser_s, const string &allergener_s) {
        assert(!ingredienser_s.empty());
        index = num;
        ingredienser = ingredienser_s;
        mulige_allergener = allergener_s;
    }

    std::string ingredienser;
    std::string mulige_allergener;
private:
    int index;
};

#endif //MATVARE_H
