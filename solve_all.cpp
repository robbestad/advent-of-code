#include <iostream>

//#include "source/2020/day_6/main.h"
#include "source/2020/7.h"
#include "source/2020/7_2.h"
#include "source/2020/8.h"
#include "source/2020/8_2.h"
#include "source/2020/9.h"
#include "source/2020/10.h"
#include "source/2019/1.h"
#include "source/2020/11.h"
#include "source/2020/12.h"
#include "source/2020/12_2.h"
#include "source/2020/13.h"
#include "source/2020/13_2.h"


int main() {
    day7::parse_input("../input/7.txt");
    std::cout << "7-1: " << day7::solve() << std::endl;

    day7b::parse_input("../input/7.txt");
    std::cout << "7-2: " << day7b::solve() << std::endl;

    day8::parse_input("../input/8.txt");
    std::cout << "8-1: " << day8::solve() << std::endl;

    day8_2::parse_input("../input/8.txt");
    std::cout << "8-2: " << day8_2::solve() << std::endl;

    day9::parse_input("../input/9.txt");
    std::cout << "9 part 1: " << day9::part1fast() << std::endl;
    day9::parse_input("../input/9.txt");
    std::cout << "9 part 2 (Kent): " << day9::part2() << std::endl;


    auto day2019input = day2019_1::parse_input("../input/2019_1.txt");
    std::cout << "2019 part 1: " << day2019_1::part1(day2019input) << std::endl;
    std::cout << "2019 test: " << day2019_1::test() << std::endl;
    std::cout << "2019 part 2: " << day2019_1::part2(day2019input) << std::endl;

    auto day10input = day10::parse_input("../input/10.txt");
    std::cout << "10 part 2 fast: " << day10::part2fast(day10input) << std::endl;
    std::cout << "10 part 2 slow: " << day10::count(day10input) << std::endl;


    std::vector<std::string> day11input = utils::read_all_lines<std::string>("../input/11.txt");
    auto[resultday11a, time_takenday11a] = day11::part1(day11input);
    std::cout << "11 part 1: " << resultday11a << " (" << time_takenday11a << " ms)" << std::endl;
    auto[resultday11b, time_takenday11b] = day11::part2(day11input);
    std::cout << "11 part 2: " << resultday11b << " (" << time_takenday11b << " ms)" << std::endl;

    std::vector<std::string> day12input = utils::read_all_lines<std::string>("../input/12.txt");
    auto[resultday12A, time_takenday12a] = day12::part1(day12input);
    std::cout << "12 part 1: " << resultday12A << " (" << time_takenday12a << "us)" << std::endl;
    auto[resultday12b, time_takenday12b] = day12_2::part2(day12input);
    std::cout << "12 part 2: " << resultday12b << " (" << time_takenday12b << "us)" << std::endl;

    std::vector<std::string> day13input = utils::read_all_lines<std::string>("./input/13.txt");
    day13::part1("13 part 1", day13input);
    day13::part2("13 part 2", day13input);


}
