#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "NotImplementedException.h"
using namespace std;

#include "Day11.h"

Day11::Day11() {
    day = 11;
    filename = "input/Day11.txt";
}

int Day11::puzzle1() {
    dropEnergyOnFlash(); //init flash array
    fillData(); //init sea array
    long flashes = 0;
    for (int step = 1; step <= 100; step++) {
        flashes += doStep(step);
    }
    return flashes;
}

int Day11::puzzle2() {
    dropEnergyOnFlash(); //init flash array
    fillData(); //init sea array

    int step{};
    for (step = 1; step <= std::numeric_limits<int>::max(); step++) {
        long flashes = doStep(step);
        if (flashes == 100) break;
    }
    return step;
}

void Day11::fillData() {
    ifstream ifs(filename, ios::binary);
    string linefile;
    int ret = 0;
    int line = 0;
    while (getline(ifs, linefile)) {
        for (int i = 0; i < 10; i++) {
            sea[line][i] = linefile[i] - '0';
        };
        line++;
    }
}

int Day11::doStep(int step) {
    energyByOne();
    doFlash();
    return dropEnergyOnFlash();
}

void Day11::energyByOne() {
    //Energy level increases by 1
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            increaseCurrent(r, c, false);
        }
    }
}

void Day11::increaseAdjacent(int r, int c) {
    for (int row = r - 1; row <= r + 1; row++) {
        for (int col = c - 1; col <= c + 1; col++) {
            if (r == row && c == col) continue; //skip current
            increaseCurrent(row, col, true);
        }
    }
}

void Day11::increaseCurrent(int r, int c, bool spread) {
    if (r >= 0 && r < 10 && c >= 0 && c < 10) {
        sea[r][c]++;
        if (spread && sea[r][c] > 9 && !flash[r][c]) {
            flash[r][c] = true;
            increaseAdjacent(r, c);
        }
    }
}

void Day11::doFlash() {
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            if (sea[r][c] > 9 && !flash[r][c]) {
                flash[r][c] = true;
                increaseAdjacent(r, c);
            }
        }
    }
}

bool Day11::dropEnergyCurrent(int r, int c) {
    if (r >= 0 && r < 10 && c >= 0 && c < 10 && flash[r][c]) {
        sea[r][c] = 0;
        return true;
    }
    return false;
}

int Day11::dropEnergyOnFlash() {
    int flashes = 0;
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            flashes += dropEnergyCurrent(r, c);
            flash[r][c] = false;
        }
    }
    return flashes;
}