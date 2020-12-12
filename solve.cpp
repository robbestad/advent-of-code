#include <iostream>


#include "source/2020/12.h"
#include "source/2020/12_2.h"

/*

 #include "source/2020/day_6/main.h"
#include "source/2020/7.h"
#include "source/2020/7_2.h"
#include "source/2020/8.h"
#include "source/2020/8_2.h"
#include "source/2020/9.h"
#include "source/2020/10.h"
#include "source/2019/1.h"
#include "source/2020/11.h"
 #include "source/2020/12.h"
#include "source/2020/13.h"
#include "source/2020/14.h"
#include "source/2020/15.h"
#include "source/2020/16.h"
#include "source/2020/17.h"
#include "source/2020/18.h"
#include "source/2020/19.h"
#include "source/2020/20.h"
#include "source/2020/21.h"
#include "source/2020/22.h"
#include "source/2020/23.h"
#include "source/2020/24.h"
#include "source/2020/25.h"
*/


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


    day9::parse_input("input/9.txt");
    std::cout << "9 part 1: " << day9::part1fast() << std::endl;
    day9::parse_input("input/9.txt");
    std::cout << "9 part 2 (Kent): " << day9::part2() << std::endl;

    day10::parse_input("input/10.txt");
    std::cout << "10 part 1: " << day10::part1() << std::endl;

    auto day2019input = day2019_1::parse_input("input/2019_1.txt");
    std::cout << "2019 part 1: " << day2019_1::part1(day2019input) << std::endl;
    std::cout << "2019 test: " << day2019_1::test() << std::endl;
    std::cout << "2019 part 2: " << day2019_1::part2(day2019input) << std::endl;

    auto day10input = day10::parse_input("input/10.txt");
    std::cout << "10 part 2 slow: " << day10::count(day10input) << std::endl;
    std::cout << "10 part 2 fast: " << day10::part2fast(day10input) << std::endl;

    std::vector<std::string> day11input = utils::read_all_lines<std::string>("./input/11.txt");
    auto[resultday11a, time_takenday11a] = day11::part1(day11input);
    std::cout << "11 part 1: " << resultday11a << " (" << time_takenday11a << " ms)" << std::endl;
    auto[resultday11b, time_takenday11b] = day11::part2(day11input);
    std::cout << "11 part 2: " << resultday11b << " (" << time_takenday11b << " ms)" << std::endl;
*/
    std::vector<std::string> day12input = utils::read_all_lines<std::string>("../input/12.txt");
    auto[resultday12A, time_takenday12a] = day12::part1(day12input);
    std::cout << "12 part 1: " << resultday12A << " (" << time_takenday12a << "us)" << std::endl;
    auto[resultday12b, time_takenday12b] = day12_2::part2(day12input);
    std::cout << "12 part 2: " << resultday12b << " (" << time_takenday12b << "us)" << std::endl;


/*
     day12::parse_input("input/12_input");
     std::cout << "12 part 1: " << day12::part1() << std::endl;
     day12::parse_input("input/12_input");
     std::cout << "12 part 2: " << day12::part2() << std::endl;


     day13::parse_input("input/13_input");
     std::cout << "13 part 1: " << day13::part1() << std::endl;
     day13::parse_input("input/13_input");
     std::cout << "13 part 2: " << day13::part2() << std::endl;


     day14::parse_input("input/14_input");
     std::cout << "14 part 1: " << day14::part1() << std::endl;
     day14::parse_input("input/14_input");
     std::cout << "14 part 2: " << day14::part2() << std::endl;


     day15::parse_input("input/15_input");
     std::cout << "15 part 1: " << day15::part1() << std::endl;
     day15::parse_input("input/15_input");
     std::cout << "15 part 2: " << day15::part2() << std::endl;


     day16::parse_input("input/16_input");
     std::cout << "16 part 1: " << day16::part1() << std::endl;
     day16::parse_input("input/16_input");
     std::cout << "16 part 2: " << day16::part2() << std::endl;


     day17::parse_input("input/17_input");
     std::cout << "17 part 1: " << day17::part1() << std::endl;
     day17::parse_input("input/17_input");
     std::cout << "17 part 2: " << day17::part2() << std::endl;


     day18::parse_input("input/18_input");
     std::cout << "18 part 1: " << day18::part1() << std::endl;
     day18::parse_input("input/18_input");
     std::cout << "18 part 2: " << day18::part2() << std::endl;


     day19::parse_input("input/19_input");
     std::cout << "19 part 1: " << day19::part1() << std::endl;
     day19::parse_input("input/19_input");
     std::cout << "19 part 2: " << day19::part2() << std::endl;


     day20::parse_input("input/20_input");
     std::cout << "20 part 1: " << day20::part1() << std::endl;
     day20::parse_input("input/20_input");
     std::cout << "20 part 2: " << day20::part2() << std::endl;


     day21::parse_input("input/21_input");
     std::cout << "21 part 1: " << day21::part1() << std::endl;
     day21::parse_input("input/21_input");
     std::cout << "21 part 2: " << day21::part2() << std::endl;


     day22::parse_input("input/22_input");
     std::cout << "22 part 1: " << day22::part1() << std::endl;
     day22::parse_input("input/22_input");
     std::cout << "22 part 2: " << day22::part2() << std::endl;


     day23::parse_input("input/23_input");
     std::cout << "23 part 1: " << day23::part1() << std::endl;
     day23::parse_input("input/23_input");
     std::cout << "23 part 2: " << day23::part2() << std::endl;


     day24::parse_input("input/24_input");
     std::cout << "24 part 1: " << day24::part1() << std::endl;
     day24::parse_input("input/24_input");
     std::cout << "24 part 2: " << day24::part2() << std::endl;


     day25::parse_input("input/25_input");
     std::cout << "25 part 1: " << day25::part1() << std::endl;
     day25::parse_input("input/25_input");
     std::cout << "25 part 2: " << day25::part2() << std::endl;
 */

}
