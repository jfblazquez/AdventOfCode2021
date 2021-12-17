#pragma once
#include "BaseDay.h"

class Day17 : 
    public BaseDay {    
public:
    Day17();
    int puzzle1();
    int puzzle2();
private:

    bool hitxTarget(int initial);
    bool hityTarget(int initial);
    bool isHit(int x, int y);
    bool makeHit(int sx, int sy);
    bool inRange(int x, int y);
    int x1{}, x2{}, y1{}, y2{};

};

