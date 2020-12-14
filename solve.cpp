#include <iostream>


#include "source/2020/12.h"
#include "source/2020/12_2.h"
#include "source/2020/13.h"
#include "source/2020/13_2.h"
#include "source/2020/14.h"

int main() {


    std::vector<std::string> day13input = utils::read_all_lines<std::string>("./input/13.txt");
    day13::part1("13 part 1", day13input);
    day13::part2("13 part 2", day13input);

    std::vector<std::string> day4_input = utils::read_all_lines<std::string>("./input/14.txt");
    std::vector<std::string> day4_test_input = utils::read_all_lines<std::string>("./input/14t.txt");
    //day14::part1("14 part 1", day4_input);
    day14::part1("14 part 1 test", day4_test_input);

}
