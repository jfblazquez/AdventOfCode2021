#pragma once
#include "BaseDay.h"

class Day13 : 
    public BaseDay {    
public:
    Day13();
    int puzzle1();
    void fillData();
    int puzzle2();
    void fold(int);
    int getMapVal(int x, int y);
    void setMapVal(int x, int y, int val);
    int countDots();
    void printMap();
private:
    bool fillDone = false;
    vector<vector<int>> map;
    vector<int> folding;
    int xsize{};
    int ysize{};
};

