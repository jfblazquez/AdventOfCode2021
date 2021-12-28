#pragma once
#include <vector>
#include <string>
#include "BaseDay.h"


class Day20 : 
    public BaseDay {    
public:
    Day20();
    int puzzle1();
    int puzzle2();
private:
    void fillData();
    int launchEnhance(int pass);

    array<bool, 512> enhancement;
    vector<vector<bool>> image;
    vector<vector<bool>> imageEn;
    void expandImageSize(int size);
    void enhance(int x, int y);
    bool getVal(int x, int y);
    int printImage(vector<vector<bool>>& i, string text);
    void removeBorders();
    
};

