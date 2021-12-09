#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <array>
#include <numeric>
using namespace std;

#include "Day6.h"

Day6::Day6() {
    day = 6;
    filename = "input/day6.txt";
}

int Day6::puzzle1() {
    return (int)solve(80);
}

int Day6::puzzle2() {
    long long ret = solve(256);
    cout << "Day 6 puzzle 2: " << ret << endl;
    return -1; //warning: bigger than int (the valid answer is the output of this method)
}

long long Day6::solve(int days)
{
    ifstream ifs(filename, ios::binary);
    vector<int> lfishsinitial;
    string strstream;

    std::array<long long, 9> lfage = { 0,0,0,0,0,0,0,0,0 };
    while (getline(ifs, strstream, ',')) {
        int lfish(stoi(strstream));
        lfage[lfish]++;
    }

    for (int day = 1; day <= days; day++) {
        std::array<long long, 9> lfageDay = { 0,0,0,0,0,0,0,0,0 };
        lfageDay[6] += lfage[0];
        lfageDay[8] += lfage[0];
        for (size_t age = 1; age <= 8; age++) {
            lfageDay[age - 1] += lfage[age];
        }
        lfage = lfageDay;
    }

    return std::accumulate(lfage.begin(), lfage.end(), (long long)0);
}