#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <numeric>
using namespace std;

#include "Day7.h"

Day7::Day7() {
    day = 7;
    filename = "input/Day7.txt";
}

int Day7::puzzle1() {
    return solve(true);
}

int Day7::puzzle2() {
    return solve(false);
}

int Day7::solve(bool basicFuel) {
    ifstream ifs(filename, ios::binary);
    vector<int> crabs;
    string strstream;

    while (getline(ifs, strstream, ',')) {
        crabs.push_back(stoi(strstream));
    }

    //hint start average
    int hMove = std::accumulate(crabs.begin(), crabs.end(), 0) / crabs.size(); 

    while (true) {
        int fuel{}, fuelup{}, fueldown{};
        for (auto crab : crabs) {     
            fuelup += fuelForPos(abs(crab - (hMove + 1)), basicFuel);            
            fuel += fuelForPos(abs(crab - hMove), basicFuel);
            fueldown += fuelForPos(abs(crab - (hMove - 1)), basicFuel);
        }
        if (fuel < fuelup && fuel < fueldown) return fuel;
        if (fuelup < fuel) hMove++;
        else hMove--;
    }

    return 0;
};

int Day7::fuelForPos(int pos, bool basicFuel) {
    if (basicFuel) return pos;
    return (pos * (pos + 1)) / 2;
}