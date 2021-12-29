#include <iostream>
#include <fstream>
#include <string>
#include "NotImplementedException.h"
using namespace std;

#include "Day21.h"

Day21::Day21() {
    day = 21;
    filename = "input/Day21.txt";
}

int Day21::puzzle1() {
    fillData();
    bool finish = false;
    while (!finish) {
        int rolls = getDiceVal() + getDiceVal() + getDiceVal();        
        scoreP1 += moveNewPos(posP1, rolls);
        finish = scoreP1 >= 1000;
        if (!finish) {
            rolls = getDiceVal() + getDiceVal() + getDiceVal();
            scoreP2 += moveNewPos(posP2, rolls);
            finish = scoreP2 >= 1000;
        }
    }

    int ret = min(scoreP1, scoreP2) * numRolls;
    return ret;
}


int Day21::puzzle2() {
    throw NotImplementedException();
}

int Day21::getDiceVal() {
    numRolls++;
    diceVal = (diceVal % 100) + 1;
    return diceVal;
}

int Day21::moveNewPos(int& playerPos, int value) {
    playerPos = ((playerPos + value - 1) % 10) + 1;
    return playerPos;
}

void Day21::fillData() {
    ifstream ifs(filename);
    string line;
    getline(ifs, line);
    posP1 = *(line.end() - 1) - '0';
    getline(ifs, line);
    posP2 = *(line.end() - 1) - '0';
}