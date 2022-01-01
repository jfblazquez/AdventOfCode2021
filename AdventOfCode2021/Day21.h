#pragma once
#include "BaseDay.h"

class Day21 : 
    public BaseDay {    
public:
    Day21();
    int puzzle1();
    void fillData();
    int puzzle2();

private:
    int getDiceVal();
    int moveNewPos(int& playerPos, int value);
    pair<long long, long long> play(int score1, int score2, int pos1, int pos2, int val1, int val2, bool& firstWin);
    int getUniv(int val);

    int diceVal{};
    int scoreP1{};
    int scoreP2{};
    int posP1{};
    int posP2{};
    int numRolls{};
    int dieSides{};
    long long winsP1{};
    long long winsP2{};
};


