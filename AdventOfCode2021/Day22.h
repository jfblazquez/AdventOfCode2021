#pragma once
#include <array>
#include <vector>
#include <limits>
#include "BaseDay.h"

using namespace std;

class Region
{
public:
    bool on{ false };
    array <int, 3> init{ 0,0,0 };
    array <int, 3> end{ 0,0,0 };
    bool contains(int x, int y, int z);
    void remove(Region& r, vector<Region>& newRegions);
    bool off() {
        return !on;
    }
    long long size();
};

class RegionAlgorithm
{
public: 
    static bool intersect(Region& r1, Region& r2);
};

class Day22 : 
    public BaseDay {    
public:
    Day22();
    int puzzle1();
    int puzzle2();
private:

    int size = 50;
    int arraysize = (2 * size) + 1;
    array <int, 3> minVal{ numeric_limits<int>::max(),numeric_limits<int>::max(),numeric_limits<int>::max() };
    array <int, 3> maxVal{ numeric_limits<int>::min(),numeric_limits<int>::min(),numeric_limits<int>::min() };

    void fillData();
    void updateMinMax(Region& r);
    vector<Region> regions;
};



