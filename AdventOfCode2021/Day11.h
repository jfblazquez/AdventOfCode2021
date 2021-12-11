#pragma once
#include <array>
#include "BaseDay.h"

class Day11 : 
    public BaseDay {    
public:
    Day11();
    int puzzle1();
    int puzzle2();
private:
    void fillData();
    int doStep(int);
    void energyByOne();
    void increaseAdjacent(int r, int c);
    void increaseCurrent(int r, int c, bool spread);
    void doFlash();
    int countFlash();
    int resetEnergy();
    int dropEnergyOnFlash();
    bool dropEnergyCurrent(int, int);
    array<array <int, 10>, 10> sea;
    array<array <int, 10>, 10> flash;
};

