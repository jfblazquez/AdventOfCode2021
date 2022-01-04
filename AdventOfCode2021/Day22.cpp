#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "NotImplementedException.h"
using namespace std;

#include "Day22.h"

Day22::Day22() {
    day = 22;
    filename = "input/Day22.txt";
}

int Day22::puzzle1() {

    fillData();
    long long ret = 0;

    for (int x = -size; x <= size; x++) {
        for (int y = -size; y <= size; y++) {
            for (int z = -size; z <= size; z++) {
                bool status = false;
                for (auto& r : regions) {
                    if (status && r.off()) {
                        if (r.contains(x, y, z)) {
                            status = false;
                        }
                    }
                    else if (!status && r.on) {
                        if (r.contains(x, y, z)) {
                            status = true;
                        }
                    }
                }
                if (status) {
                    ret++;
                }
            }
        }
    }
    return ret;
}

int Day22::puzzle2() {
    fillData();
    long long ret = 0;

    for (int x = minVal[0]; x <= maxVal[0]; x++) {
        for (int y = minVal[1]; y <= maxVal[1]; y++) {
            for (int z = minVal[2]; z <= maxVal[2]; z++) {
                bool status = false;
                for (auto& r : regions) {
                    if (status && r.off()) {
                        if (r.contains(x, y, z)) {
                            status = false;
                        }
                    }
                    else if (!status && r.on) {
                        if (r.contains(x, y, z)) {
                            status = true;
                        }
                    }
                }
                if (status) {
                    ret++;
                }
            }
        }
    }
    cout << endl << "sol: " << ret << endl;
    return ret;
}

void Day22::fillData()
{
    regions.clear();
    ifstream ifs(filename);    
    string line;
    while (getline(ifs, line)) {
        Region r;
        stringstream ss(line);
        r.on = line[1] == 'n';
        ss.ignore(r.on ? 5 : 6);
        //x
        ss >> r.init[0];
        ss.ignore(2);
        ss >> r.end[0];
        ss.ignore(3);
        //y
        ss >> r.init[1];
        ss.ignore(2);
        ss >> r.end[1];
        ss.ignore(3);
        //z
        ss >> r.init[2];
        ss.ignore(2);
        ss >> r.end[2];
        updateMinMax(r);
        regions.push_back(r);
    }
}

void Day22::updateMinMax(Region& r)
{
    for (int i = 0; i < 3; i++) {
        if (minVal[i] > r.init[i]) {
            minVal[i] = r.init[i];
        }
        if (maxVal[i] < r.end[i]) {
            maxVal[i] = r.end[i];
        }
    }
}

bool Region::contains(int x, int y, int z)
{
    return x >= init[0] && x <= end[0] &&
        y >= init[1] && y <= end[1] &&
        z >= init[2] && z <= end[2];
}
