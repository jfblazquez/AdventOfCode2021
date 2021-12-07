#pragma once
#include "BaseDay.h"

class Day7 : 
    public BaseDay {    
public:
    Day7();
    int puzzle1();
    int puzzle2();
    int solve(bool basicFuel);
    int fuelForPos(int pos, bool basicFuel);

};

