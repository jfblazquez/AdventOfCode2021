#pragma once
#include "BaseDay.h"

class Day6 : 
    public BaseDay {    
public:
    Day6();
    int puzzle1();
    int puzzle2();
    vector<int> numbersToVector(string);
};

