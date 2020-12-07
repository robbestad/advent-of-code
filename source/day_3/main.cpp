#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int countTrees(int dx, int dy, const vector<string> &map) {
    int it = 0;
    int trees = 0;
    int cursor = dx;
    int width = map.at(0).size();

    while (it <= map.size()) {
        it += dy;
        if (map[it][cursor] == '#') {
            trees += 1;
        }
        cursor += dx;
        cursor %= width;
    }
    return trees;
}

vector<string> lesFil(string const &fil) {
    ifstream inFile;

    inFile.open(fil);
    vector<string> map;
    if (inFile.fail()) {
        cerr << "Fil kunne ikke åpnes" << endl;
        inFile.close();
        exit(1);
    }

    string row;
    int num = 0;
    while (getline(inFile, row)) {
        num++;
        map.push_back(row);
    }
    inFile.close();
    return map;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Angi input-fil som param" << endl;
        exit(1);
    }
    vector<string> map = lesFil(argv[1]);

    int part1 = countTrees(3, 1, map);
    cout << part1 << " trær" << endl;

    int64_t part2 =
            ((int64_t) countTrees(1, 1, map)
             * countTrees(3, 1, map)
             * countTrees(5, 1, map)
             * countTrees(7, 1, map)
             * countTrees(1, 2, map));
    cout << part2 << " trær" << endl;
}

