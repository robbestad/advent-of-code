#include <iostream>
#include <fstream>
#include <vector>
#include "../split.hpp"

int main()
{
	std::ifstream inFile;
	inFile.open("input_complete");
	if (inFile.fail()) {
		std::cerr << "Fil kunne ikke åpnes" << std::endl;
		inFile.close();
		exit(1);
	}
	std::string line;
	int valid1 = 0;
	int valid2 = 0;
	while (getline(inFile, line))
	{
		std::string space = " ";
		std::string dash = "-";
		std::vector<std::string> v = split (line, space);
		std::vector<std::string> o = split(v[0], dash);
		char c = v.at(1).c_str()[0];

		int min = stoi(o.at(0))-1;
		int max = stoi(o.at(1))-1;
		int count = std::count(v[2].begin(), v[2].end(), c);

		if(count >= min+1 && count <= max+1){
			valid1++;
		}

		if (v[2][min] == c ^ v[2][max] == c)
			valid2++;
	}
	inFile.close();

	std::cout << valid1 << " part1 valid" << std::endl;
	std::cout << valid2 << " part2 valid" << std::endl;
}

