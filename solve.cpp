#include <iostream>


#include "source/2020/12.h"
#include "source/2020/12_2.h"
#include "source/2020/13.h"
#include "source/2020/13_2.h"
#include "source/2020/14.h"

int main() {
    
    std::vector<std::string> day4input = utils::read_all_lines<std::string>("./input/14t.txt");
    day14::part1("14 part 1", day4input);
    day14::part2("14 part 2", day4input);

}
