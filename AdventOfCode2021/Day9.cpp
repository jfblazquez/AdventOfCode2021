#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

#include "Day9.h"



Day9::Day9() {
    day = 9;
    filename = "input/Day9.txt";
}

int Day9::puzzle1() {
    Filldata();

    int ret = 0;
    for (int x = 0; x < CSIZE; x++) {
        for (int y = 0; y < CSIZE; y++) {
            ret += lowPointVal(x, y);
        }
    }

    return ret;
}

int Day9::puzzle2() {
    Filldata();
    vector < pair<int, int>> lowPoints;

    for (int x = 0; x < CSIZE; x++) {
        for (int y = 0; y < CSIZE; y++) {
            if (lowPointVal(x, y)) {
                lowPoints.push_back({ x,y });
                if (coords[x][y] == 9) {
                    int asd;//error?
                }
            }
        }
    }

    vector<int> basins;
    for (const auto& pair : lowPoints) {
        auto [x, y] = pair;
        basins.push_back(basin(x, y));
    }

    std::sort(basins.begin(), basins.end());
    int ret = 1;
    for (auto pos = basins.size() - 1; pos >= basins.size() - 3 && pos >= 0; pos--) {
        ret *= basins[pos];
    }

    return ret;
}


void Day9::Filldata()
{
    ifstream ifs(filename, ios::binary);
    string linefile;
    int line = 0;
    while (getline(ifs, linefile)) {
        for (int y = 0; y < CSIZE; y++) {
            coords[line][y] = linefile[y] - '0';
        }
        line++;
    }
}


int Day9::lowPointVal(int x, int y)
{    
    int val = coords[x][y];
    int left = y == 0 ? 10 : coords[x][y - 1];
    int right = y == CSIZE -1 ? 10: coords[x][y + 1];
    int up = x == 0 ? 10 : coords[x - 1][y];
    int down = x == CSIZE - 1 ? 10 : coords[x + 1][y];
    int ret = 0;
    if (val < up && val < down && val < left && val < right) {
        ret = val + 1;
    }
    return ret;
}

int Day9::basin(int x, int y)
{ 
    int val = coords[x][y];
    if (val == 8) {
        coords[x][y] = 9;
        return 1;
    }
    int ret = 1;
    coords[x][y] = 9;
    int left = y == 0 ? 10 : coords[x][y - 1];
    if (left == val + 1) ret += basin(x, y - 1);
    int right = y == CSIZE - 1 ? 10 : coords[x][y + 1];
    if (right == val + 1) ret += basin(x, y + 1);
    int up = x == 0 ? 10 : coords[x - 1][y];
    if (up == val + 1) ret += basin(x - 1, y);
    int down = x == CSIZE - 1 ? 10 : coords[x + 1][y];
    if (down == val + 1) ret += basin(x + 1, y);
    return ret;
}
