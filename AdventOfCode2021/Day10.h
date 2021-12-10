#pragma once
#include <stack>
#include "BaseDay.h"

class Day10 : 
    public BaseDay {    
public:
    Day10();
    int puzzle1();
    int puzzle2();
private:
    char topandpop(stack<char>& s);
    int ilegalPoints(string& linefile);
    long long closePoints(string& linefile);
};

