#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <array>
//#include "NotImplementedException.h"
using namespace std;

#include "Day6.h"

Day6::Day6() {
    day = 6;
    filename = "input/day6.txt";
}

int Day6::puzzle1() {
    ifstream ifs(filename, ios::binary);
    vector<int> lfishs;
    int number{};

    string strstream;
    ifs >> strstream;
    lfishs = std::move(numbersToVector(strstream));

    for (int day = 1; day <= 80; day++) {
        int newCreation{};
        for (auto& lfish : lfishs) {
            lfish--;
            if (lfish < 0) {
                lfish = 6;
                newCreation++;
            }
        }
        lfishs.insert(lfishs.end(), newCreation, 8);
        cout << day << " : " << lfishs.size() << "\n";
    }

    return lfishs.size();
}

int Day6::puzzle2() {
    ifstream ifs(filename, ios::binary);
    vector<int> lfishsinitial;

    string strstream;
    ifs >> strstream;
    lfishsinitial = std::move(numbersToVector(strstream));

    std::array<long long, 9> lfage = {0,0,0,0,0,0,0,0,0};
    

    for (auto lfish : lfishsinitial) {
        lfage[lfish]++;
    }

    for (int day = 1; day <= 256; day++) {
        std::array<long long, 9> lfageDay = { 0,0,0,0,0,0,0,0,0 };
        lfageDay[6] += lfage[0];
        lfageDay[8] += lfage[0];
        for (int age = 1; age <= 8; age++) {
            lfageDay[age - 1] += lfage[age];
        }
        lfage = lfageDay;

        long long total{};
        for (int age = 0; age <= 8; age++) {
            total += lfage[age];
        }

        cout << "day " << day << " : "  << total << endl;
    }

    return 0;
}

vector<int> Day6::numbersToVector(string str) {
    vector<int> retVector;
    std::regex regexz(",");
    vector<string> list(sregex_token_iterator(str.begin(), str.end(), regexz, -1), sregex_token_iterator());
    std::for_each(list.begin(), list.end(), [&](string s) {retVector.push_back(stoi(s));});
    return retVector;
}