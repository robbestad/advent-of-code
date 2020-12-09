#include <iostream>

#include "source/day_6/main.h"
#include "source/days/7.h"
#include "source/days/7_2.h"
#include "source/days/8.h"
#include "source/days/8_2.h"
#include "source/days/9.h"

int main() {
/*
     std::cout << "6-1: " << day6::part1() << std::endl;
     std::cout << "6-2: " << day6::part2() << std::endl;

    day7::parse_input("input/7_input.txt");
    std::cout << "7-1: " << day7::solve() << std::endl;

    day7b::parse_input("input/7_input.txt");
    std::cout << "7-2: " << day7b::solve() << std::endl;

    day8::parse_input("input/8_input.txt");
    std::cout << "8-1: " << day8::solve() << std::endl;

    day8_2::parse_input("input/8_input.txt");
    std::cout << "8-2: " << day8_2::solve() << std::endl;
    */
    day9::parse_input("input/9_input");
    std::cout << "9_1: " << day9::part1() << std::endl;
    day9::parse_input("input/9_input");
    std::cout << "9_2: " << day9::part2() << std::endl;

}
