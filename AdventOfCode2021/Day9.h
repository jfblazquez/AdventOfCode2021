#pragma once
#include "BaseDay.h"

#define CSIZE 100 //Change for test input to 10
#define TSIZE CSIZE*CSIZE

class Day9 : 
    public BaseDay {    
public:
    Day9();
    int puzzle1();
    int puzzle2();
    
private:
    array < array<int, CSIZE>, CSIZE> coords;
    int lowPointVal(int x, int y);
    int basin(int x, int y);
    void Filldata();

};

