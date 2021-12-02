#include <iostream>
#include <fstream>
#include<limits>
#include<vector>
using namespace std;

#include "Day1.h"

Day1::Day1() {
	day = 1;
	filename = "input/day1.txt";
}

int Day1::puzzle1() {
    ifstream ifs(filename, ios::binary);
    int last = std::numeric_limits<int>::max();
    int result = 0;
    while (!ifs.eof()) {
        int depth;
        ifs >> depth;
        if (depth > last) {
            result++;
        }
        last = depth;
    }

    return result;
}

int Day1::puzzle2() {
    ifstream ifs(filename, ios::binary);
    int last = std::numeric_limits<int>::max();
    int result = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    ifs >> a;
    ifs >> b;
    ifs >> c;
    vector<int> v;
    v.push_back(a + b + c);
    while (!ifs.eof()) {
        a = b;
        b = c;
        ifs >> c;
        if (ifs.eof()) break;
        v.push_back(a + b + c);
    }

    for (int depth : v) {

        ifs >> depth;
        if (depth > last) {
            result++;
        }
        last = depth;
    }
    return result;
}