#pragma once
#include <vector>
#include <string>
#include <array>
#include "BaseDay.h"

using namespace std;

class Board
{
public:
    array<int, 25> arrayValues;
    void mark(int number); //changes from + to -
    int  unmarked(); //return all +
    bool bingo(); //check if row or column all -
    void add(int pos, int number); //fill board
};

class Day4 : 
    public BaseDay {    
public:
    Day4();
    int puzzle1();
    int puzzle2();
    void FillData(vector<int>&, vector<Board>&);
    vector<int> numbersToVector(string);
};

