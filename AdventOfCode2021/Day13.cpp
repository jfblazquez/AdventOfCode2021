#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

#include "Day13.h"

#define SIZE 1500
Day13::Day13() {
    day = 13;
    filename = "input/Day13.txt";
}

int Day13::puzzle1() {
    fillData();
    fold(folding[0]);
    return countDots();
}

int Day13::puzzle2() {
    fillData();
    for_each(folding.begin(), folding.end(), [this](auto f) {fold(f);});
    cout << "Day 13 puzzle 2: ";
    printMap();
    return numeric_limits<int>::max();
}

void Day13::fillData()
{
    ifstream ifs(filename, ios::binary);
    map.clear();
    folding.clear();
    xsize = SIZE;
    ysize = SIZE;

    map.insert(map.begin(), SIZE, vector<int>());
    for_each(map.begin(), map.end(), [](auto& v) {v.insert(v.begin(), SIZE, 0);});

    string strstream;

    bool readingCoords = true;
    while (getline(ifs, strstream)) {
        if (strstream != "") {
            if (readingCoords) {
                auto pos = strstream.find(',');

                int x = stoi(strstream.substr(0, pos));
                int y = stoi(strstream.substr(pos + 1, strstream.size()));
                if (y >= SIZE || x >= SIZE) cout << "ERR" << endl;
                map[y][x] = 1;
            }
            else {
                //+ for x - for y
                int mult = strstream.find('x') != string::npos ? +1 : -1;
                auto pos = strstream.find('=');
                string substr = strstream.substr(pos + 1, strstream.size());
                int foldNumber = stoi(substr);
                folding.push_back(mult * foldNumber);
            }
        }
        else {
            readingCoords = false;
        }
    }
}

void Day13::fold(int folding)
{
    //+ for x - for y
    if (folding > 0) {
        for (int f = folding + 1, fm = folding -1; f < xsize; f++, fm--) {
            for (int y = 0; y < ysize; y++) {
                int val = getMapVal(fm, y) + getMapVal(f, y);
                setMapVal(fm, y, val);
            }
        }
        xsize = folding;
    }
    else {
        folding *= -1;
        for (int f = folding + 1, fm = folding - 1; f < ysize; f++, fm--) {
            for (int x = 0; x < xsize; x++) {
                int val = getMapVal(x, fm) + getMapVal(x, f);
                setMapVal(x, fm, val);
            }
        }
        ysize = folding;
    }
}

int Day13::getMapVal(int x, int y)
{
    bool validX = x >= 0 && x < xsize;
    bool validY = y >= 0 && y < ysize;
    if (validX && validY) {
        return map[y][x];
    }
    return 0;
}

void Day13::setMapVal(int x, int y, int val)
{
    bool validX = x >= 0 && x < xsize;
    bool validY = y >= 0 && y < ysize;
    if (validX && validY) {
        map[y][x] = val;
    }
}

int Day13::countDots()
{
    int ret = 0;
    for (int x = 0; x < xsize; x++) {
        for (int y = 0; y < ysize; y++) {
            if (map[y][x] != 0) {
                ret++;
            }
        }
    }
    return ret;
}

void Day13::printMap()
{
    cout << endl;
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {       
            cout << (char)((map[y][x] != 0) ? 219 : 32); //Full char or space
        }
        cout << endl;
    }
}
