#include <iostream>


#include "source/2020/13.h"


int main() {
    std::vector<std::string> day13input = utils::read_all_lines<std::string>("./input/13.txt");
    auto[resultday13A, time_takenday13a] = day13::part1(day13input);
    std::cout << "13 part 1: " << resultday13A << " (" << time_takenday13a << "us)" << std::endl;


}
