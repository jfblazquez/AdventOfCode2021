#pragma once
#include "BaseDay.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

class Day14 : 
    public BaseDay {    
public:
    Day14();
    int puzzle1();

    int puzzle2();
private:
    void fillData();
    long long result();
    string polymerize();
    void polymerizeComplex(string, int);

    map<string, string> iRules;    
    map<char, long long> elemsDebug;
    vector<long long> elemsV;
    string iPolymer;
    map<string, long long> pairs;

};

