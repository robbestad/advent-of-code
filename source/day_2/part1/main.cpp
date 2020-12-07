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
	int valid = 0;
	while (getline(inFile, line))
	{
		std::string space = " ";
		std::string dash = "-";
		std::vector<std::string> v = split (line, space);
		std::vector<std::string> o = split(v[0], dash);
		char s_char[v[1].length()+1];
		strcpy(s_char, v[1].c_str());
		int min = stoi(o[0]);
		int max = stoi(o[1]);
		int num = std::count(v[2].begin(), v[2].end(), s_char[0]);

		if(num >= min && num <= max){
			valid++;
		}
	}
	std::cout << valid << " valid" << std::endl;
	inFile.close();
}

