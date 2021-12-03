#pragma once
#include "BaseDay.h"

class Day3 : 
    public BaseDay {    
public:
    Day3();
    int puzzle1();
    int puzzle2();
private:
    int locateVal(const vector<int>&, bool control);
};

