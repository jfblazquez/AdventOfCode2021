#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
    vector<Region> boot;
    for (Region& r : regions) {
        //if r.off call remove on all boot regions
        vector<Region> newRegions;
        for (Region& b : boot) {
            if (RegionAlgorithm::intersect(b, r)) {
                b.remove(r, newRegions);
            }
        }
        if (r.on) {
            //if r.on  swith off that range on all boot regions (like before) then copy region to boot
            boot.push_back(r);
        }
        boot.insert(boot.end(), newRegions.begin(), newRegions.end());

    }

    long long ret = 0;
    for (Region& b : boot) {
        if (b.on) {
            ret += b.size();
        }
    }

    cout << "Day: " << this->getDay() << " puzzle2: " << ret << "\n";
    return numeric_limits<int>::max();
}

void Day22::fillData() {
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

void Day22::updateMinMax(Region& r) {
    for (int i = 0; i < 3; i++) {
        if (minVal[i] > r.init[i]) {
            minVal[i] = r.init[i];
        }
        if (maxVal[i] < r.end[i]) {
            maxVal[i] = r.end[i];
        }
    }
}

bool Region::contains(int x, int y, int z) {
    return x >= init[0] && x <= end[0] &&
        y >= init[1] && y <= end[1] &&
        z >= init[2] && z <= end[2];
}

void Region::remove(Region& black, vector<Region>& newRegions) {
    if (off()) return;

    auto& white = *this;
    Region refer(white);

    for (int coord = 0; coord < 3; coord++) {

        if (black.init[coord] > white.init[coord]) {
            Region r(refer);
            r.end[coord] = black.init[coord] - 1;
            newRegions.push_back(r);
        }

        if (black.end[coord] < white.end[coord]) {
            Region r(refer);
            r.init[coord] = black.end[coord] + 1;
            newRegions.push_back(r);
        }

        int coordInit = max(black.init[coord], white.init[coord]);
        int coordEnd = min(black.end[coord], white.end[coord]);
        refer.init[coord] = coordInit;
        refer.end[coord] = coordEnd;
    }

    on = false;
}

long long Region::size() {
    long long ret = 1;
    for (int i = 0; i < 3; i++) {
        ret *= (long long)((end[i] - init[i]) + 1);
    }
    return ret;
}

bool RegionAlgorithm::intersect(Region& white, Region& black) {
    bool intersect = true;
    for (int coord = 0;intersect && coord < 3; coord++) {
        intersect = black.init[coord] <= white.end[coord] && black.end[coord] >= white.init[coord];
    }
    return intersect;
}
