#include <iostream>


#include "source/2020/12.h"
#include "source/2020/12_2.h"
#include "source/2020/13.h"
#include "source/2020/13_2.h"
#include "source/2020/14_2.h"
#include "source/2020/14.h"
#include "source/2020/15.h"

int main() {

    //std::vector<std::string> day13input = utils::read_all_lines<std::string>("./input/13.txt");
    //day13::part1("13 part 1", day13input);
    //day13::part2("13 part 2", day13input);
//
    //day14::part1("14 part 1", "input/14.txt");
    //day14::part1("14 part 1 test", "input/14t.txt");
    //day14::part2("14 part 2", "input/14.txt");
    //day14::part2("14 part 2 test", "input/14.txt");
    day15::part1("15 part 1 test ", {0, 3, 6}, 2020);
    day15::part2("15 part 2 test", {0, 3, 6}, 2020);
    day15::part2("15 part 2", {7, 14, 0, 17, 11, 1, 2}, 30000000);

}
