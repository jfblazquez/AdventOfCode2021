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

    int diceVal{100};
    int scoreP1{};
    int scoreP2{};
    int posP1{};
    int posP2{};
    int numRolls{};
    
};


