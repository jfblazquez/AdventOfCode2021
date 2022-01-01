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

    //Val /universe happens
    //3,1
    //4,3
    //5,6
    //6,7
    //7,6
    //8,3
    //9,1

    pair<long, long> occurs = { 0,0 };
    int score1 = 0, score2 = 0, pos1 = 0, pos2 = 0, val1 = 0, val2 = 0;
    //auto [player1, player2] = play(0, 0, posP1, posP2, 0, 0, 0);
    pair<long long, long long> p = play(0, 0, posP1, posP2, 0, 0, 1);
    long long player1 = p.first;
    long long player2 = p.second;
    long long ret = player1 > player2 ? player2 : player1;
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

pair<long long,long long> Day21::play(int score1, int score2, int pos1, int pos2, int val1, int val2, long long univ)
{
    plays++;
    int univ1 = getUniv(val1);
    int univ2 = getUniv(val2);
    if (val1 > 0 && val2 > 0) {
        score1 += moveNewPos(pos1, val1);
        bool finish = score1 >= 21;
        if (finish) {
            return { univ + (long long)univ1,0 };
        }
        else
        {
            score2 += moveNewPos(pos2, val2);
            bool finish = score2 >= 21;
            if (finish) {
                return { 0, univ * (long long)univ2 };
            }
        }
    }
    //!finish
    pair<long long, long long> ret = { 0, 0 };
    for (int v1 = 3; v1 <= 9; v1++) {
        for (int v2 = 3; v2 <= 9; v2++) {
            pair<long long,long long> p = play(score1, score2, pos1, pos2, v1, v2, univ + univ1 + univ2);
            ret.first += p.first;
            ret.second += p.second;
            //cout << ret.first << "," << ret.second << endl;
        }
    }
    return ret;
    
}

int Day21::getUniv(int val)
{
    switch (val) {
    case 0: return 1; //start
    case 3: return 1;
    case 4: return 3;
    case 5: return 6;
    case 6: return 7;
    case 7: return 6;
    case 8: return 3;
    case 9: return 1;
    }
}

void Day21::fillData() {
    ifstream ifs(filename);
    string line;
    getline(ifs, line);
    posP1 = *(line.end() - 1) - '0';
    getline(ifs, line);
    posP2 = *(line.end() - 1) - '0';
    posP1 = 4;
    posP2 = 8;
}