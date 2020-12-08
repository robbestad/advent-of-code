//
// Created by Sven Anders Robbestad on 05/12/2020.
//

#ifndef AOC_LESFIL_H
#define AOC_LESFIL_H

std::vector<std::string> lesFil(std::string const &fil) {
    std::ifstream inFile;

    inFile.open(fil);
    std::vector<std::string> map;
    if (inFile.fail()) {
        std::cerr << "Fil kunne ikke åpnes" << std::endl;
        inFile.close();
        exit(1);
    }

    std::string row;
    std::string temp;
    while (getline(inFile, row)) {
        map.push_back(row);
    }
    map.push_back(temp);

    inFile.close();
    return map;
}
#endif //AOC_LESFIL_H
