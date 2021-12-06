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
    return solve(80);
}

int Day6::puzzle2() {
    long long ret = solve(256);
    cout << "Day: 6 puzzle2: " << ret << endl;
    return -1; //warning: bigger than int (the valid answer is the output of this method)
}

long long Day6::solve(int days)
{
    ifstream ifs(filename, ios::binary);
    vector<int> lfishsinitial;
    string strstream;
    ifs >> strstream;
    lfishsinitial = std::move(numbersToVector(strstream));

    std::array<long long, 9> lfage = { 0,0,0,0,0,0,0,0,0 };

    for (auto lfish : lfishsinitial) {
        lfage[lfish]++;
    }

    for (int day = 1; day <= days; day++) {
        std::array<long long, 9> lfageDay = { 0,0,0,0,0,0,0,0,0 };
        lfageDay[6] += lfage[0];
        lfageDay[8] += lfage[0];
        for (int age = 1; age <= 8; age++) {
            lfageDay[age - 1] += lfage[age];
        }
        lfage = lfageDay;
    }

    return std::accumulate(lfage.begin(), lfage.end(), (long long)0);
}

vector<int> Day6::numbersToVector(string str) {
    vector<int> retVector;
    std::regex regexz(",");
    vector<string> list(sregex_token_iterator(str.begin(), str.end(), regexz, -1), sregex_token_iterator());
    std::for_each(list.begin(), list.end(), [&](string s) {retVector.push_back(stoi(s));});
    return retVector;
}