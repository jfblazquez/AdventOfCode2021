#pragma once
#include "BaseDay.h"

class Day8 : 
    public BaseDay {    
public:
    Day8();
    int puzzle1();
    int puzzle2();
    void getSegments(vector<string>& input);
    vector<int> bruteForce(vector<string>& input);
    int processLine(vector<string>& lineValues);
};

