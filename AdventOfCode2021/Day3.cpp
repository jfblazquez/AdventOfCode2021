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
    bool first = true;
    int elements = 0;
    while (ifs >> data) {
        elements ++;
        int number = stoi(data, 0, 2);
        int bitpos = 0;
        int bitval = 1;
        while (bitval <= 1 << 11) {
            int value = (number & bitval) >> bitpos;
            if (first) {                
                    amount.push_back(value);
            }
            else {
                amount[bitpos] += value;
            }          
            bitval <<= 1;
            bitpos++;
        }
        first = false;
    }

    //amount is lsb order and count 1
    int halfElements = elements / 2;
    unsigned int gammaRate = 0;
    int bitval = 1;
    for (int amountOne : amount) {
        if (amountOne > halfElements) {
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

    //oxigen (most common)
    vector<int> oxigen{ vals };
    int oxigenVal = -1;
    for (int exp = 11; exp >= 0 && oxigenVal < 0; exp--) {
        int elements = oxigen.size();
        int expVal = 1 << exp;
        int ones = std::count_if(oxigen.begin(), oxigen.end(),
            [&](int i) {return (expVal) & i;});
        int keep = -1;
        if (2*ones >= elements) {
            //most common is one
            keep = 1;
        }
        else {
            keep = 0;
        }

        vector<int> temp;
        std::copy_if(oxigen.begin(), oxigen.end(), 
            std::back_inserter(temp), [&](int i) {return (i & expVal) == keep << exp;});

        oxigen = std::move(temp);

        if (oxigen.size() == 1) {
            oxigenVal = oxigen[0];
        }
    }

    //co2
    vector<int> co2{ vals };
    int co2Val = -1;
    for (int exp = 11; exp >= 0 && co2Val < 0; exp--) {
        int elements = co2.size();
        int expVal = 1 << exp;
        int ones = std::count_if(co2.begin(), co2.end(),
            [&](int i) {return (expVal)&i;});
        int keep = -1;
        if (2*ones >= elements) {
            //most common is one
            keep = 0;
        }
        else {
            keep = 1;
        }

        vector<int> temp;
        std::copy_if(co2.begin(), co2.end(),
            std::back_inserter(temp), [&](int i) {return (i & expVal) == keep << exp;});

        co2 = std::move(temp);

        if (co2.size() == 1) {
            co2Val = co2[0];
        }
    }

    int result{oxigenVal*co2Val};
    return result;
}
