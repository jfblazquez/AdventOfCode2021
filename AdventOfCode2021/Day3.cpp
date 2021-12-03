#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "Day3.h"

Day3::Day3() {
    day = 2;
    filename = "input/day3.txt";
}

int Day3::puzzle1() {
    ifstream ifs(filename, ios::binary);
    string data{};
    vector<int> amount;
    amount.insert(amount.begin(), 12, 0);
    int elements = 0;
    while (ifs >> data) {
        elements ++;
        int number = stoi(data, nullptr, 2);
        int bitpos = 0;
        int bitval = 1;
        while (bitval <= 1 << 11) {
            int value = (number & bitval) >> bitpos;
            amount[bitpos] += value;                   
            bitval <<= 1;
            bitpos++;
        }
    }

    //amount is lsb order and count 1
    unsigned int gammaRate = 0;
    int bitval = 1;
    for (int amountOne : amount) {
        if (2*amountOne > elements) {
            gammaRate += bitval;
        }
        bitval <<= 1;
    }

    unsigned int epsilonRate = ~gammaRate;
    epsilonRate = epsilonRate & 4095;
    unsigned int result { epsilonRate * gammaRate };
    return result;
}

int Day3::puzzle2() {
    ifstream ifs(filename, ios::binary);
    string data{};
    vector<int> vals;
    bool first = true;
    while (ifs >> data) {        
        int number = stoi(data, 0, 2);
        vals.push_back(number);
    }

    int oxigenVal = locateVal(vals, true);
    int co2Val = locateVal(vals, false);

    int result{oxigenVal*co2Val};
    return result;
}

int Day3::locateVal(const vector<int>& vals, bool mostCommonIsOne) {
    vector<int> currentVals{ vals };
    int ret = -1;
    for (int exp = 11; exp >= 0 && ret < 0; exp--) {
        int elements = currentVals.size();
        int expVal = 1 << exp;
        int ones = std::count_if(currentVals.begin(), currentVals.end(),
            [&](int i) {return expVal & i;});
        int numberKeep = (2 * ones >= elements) ^ !mostCommonIsOne; //When mostCommonIsOne, return 1 when above average. 

        vector<int> temp;
        std::copy_if(currentVals.begin(), currentVals.end(),
            std::back_inserter(temp), [&](int i) {return (i & expVal) == numberKeep << exp;});

        currentVals = std::move(temp);

        if (currentVals.size() == 1) {
            ret = currentVals[0];
        }
    }
    return ret;
}
