#include <iostream>
#include <fstream>
#include <string>
#include "NotImplementedException.h"
using namespace std;

#include "Day21.h"

#define MAXVAL 21
Day21::Day21() {
    day = 21;
    filename = "input/Day21.txt";
}

int Day21::puzzle1() {

    fillData();
    dieSides = 100;
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
    fillData();
    dieSides = 3;
    diceVal = 0;

    pair<long, long> occurs = { 0,0 };
    int score1 = 0, score2 = 0, pos1 = 0, pos2 = 0, val1 = 0, val2 = 0;    
    bool firstWin = false;
    auto [player1, player2] = play(0, 0, posP1, posP2, 0, 0, firstWin);
    long long ret = player1 > player2 ? player1 : player2;
    cout << "Day21: " << ret << endl;
    return ret;
}

int Day21::getDiceVal() {
    numRolls++;
    diceVal = (diceVal % dieSides) + 1;
    return diceVal;
}

int Day21::moveNewPos(int& playerPos, int value) {
    playerPos = ((playerPos + value - 1) % 10) + 1;
    return playerPos;
}

pair<long long,long long> Day21::play(int score1, int score2, int pos1, int pos2, int val1, int val2, bool& firstWin) {
    if (val1 > 0 && val2 > 0) {
        score1 += moveNewPos(pos1, val1);

        bool finish = score1 >= MAXVAL;
        if (finish) {
            firstWin = true;
            return {1, 0};
        }
        else
        {
            score2 += moveNewPos(pos2, val2);
            bool finish = score2 >= MAXVAL;
            if (finish) {
                return {0, 1};
            }
        }
    }
    //!finish
    pair<long long, long long> ret = { 0, 0 };
    for (int v1 = 3; v1 <= 9; v1++) {
        for (int v2 = 3; v2 <= 9; v2++) {
            bool firstWin = false;
            pair<long long,long long> p = play(score1, score2, pos1, pos2, v1, v2, firstWin);
            int univ = getUniv(v1);
            if (!firstWin)
            {
                univ *= getUniv(v2);
            }
            ret.first += univ * p.first;
            ret.second += univ * p.second;
            if (firstWin) {
                firstWin = false;
                break;
            }
        }
    }
    return ret;
    
}

int Day21::getUniv(int val) {
    //Val /universe freq
    switch (val) {
    case 0: return 1; //start
    case 3: return 1;
    case 4: return 3;
    case 5: return 6;
    case 6: return 7;
    case 7: return 6;
    case 8: return 3;
    case 9: return 1;
    default: throw 1;
    }
}

void Day21::fillData() {
    ifstream ifs(filename);
    string line;
    getline(ifs, line);
    posP1 = *(line.end() - 1) - '0';
    getline(ifs, line);
    posP2 = *(line.end() - 1) - '0';
    //posP1 = 4;
    //posP2 = 8;
}