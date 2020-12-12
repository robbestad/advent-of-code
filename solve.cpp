#include <iostream>


#include "source/2020/12.h"
#include "source/2020/12_2.h"


int main() {
    std::vector<std::string> day12input = utils::read_all_lines<std::string>("../input/12.txt");
    auto[resultday12A, time_takenday12a] = day12::part1(day12input);
    std::cout << "12 part 1: " << resultday12A << " (" << time_takenday12a << "us)" << std::endl;
    auto[resultday12b, time_takenday12b] = day12_2::part2(day12input);
    std::cout << "12 part 2: " << resultday12b << " (" << time_takenday12b << "us)" << std::endl;


}
