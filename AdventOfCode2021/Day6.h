#pragma once
#include "BaseDay.h"

class Day6 : 
    public BaseDay {    
public:
    Day6();
    int puzzle1();
    int puzzle2();
    long long solve(int days);
    vector<int> numbersToVector(string);
};

