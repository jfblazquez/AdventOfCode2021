#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

#include "Day9.h"

Day9::Day9() {
    day = 9;
    filename = "input/Day9.txt";
}

int Day9::puzzle1() {
    filldata();

    int ret = 0;
    for (int x = 0; x < CSIZE; x++) {
        for (int y = 0; y < CSIZE; y++) {
            int val = lowPointVal(x, y);
            if (val) {
                ret += val;
                lowPoints.push_back({ x,y });
            }       
        }
    }

    return ret;
}

int Day9::puzzle2() {

    if (lowPoints.size() == 0) puzzle1(); //call puzzle1 if not executed

    //paintMap("origin");
    vector<int> basins;
    for (const auto& pair : lowPoints) {
        auto [x, y] = pair;   
        int val = coords[x][y];
        int basinVal = basin(x, y);        
        basins.push_back(basinVal);
        //cout << "[" << x << "," << y << "] : " << val << " -> " << basinVal << endl;
    }
    //paintMap("end");

    std::sort(basins.begin(), basins.end());
    int ret = std::accumulate(basins.rbegin(), basins.rbegin() + 3, 1, std::multiplies<int>());

    return ret;
}


void Day9::filldata() {
    ifstream ifs(filename, ios::binary);
    string linefile;
    int line = 0;    
    while (getline(ifs, linefile)) {
        for (int y = 0; y < CSIZE; y++) {
            coords[line][y] = linefile[y] - '0';
        }
        line++;
    }
}

void Day9::paintMap(const string& statusText) {
    cout << "--------------" << statusText <<"--------------" << endl;
    for (int x = 0; x < CSIZE; x++) {
        for (int y = 0; y < CSIZE; y++) {
            int val = coords[x][y];
            
            if (val > 9 || val < 0) cout << '#';
            else cout << val; 
            cout << " ";
        }
        cout << endl;
    }
}


int Day9::lowPointVal(int x, int y) {    
    int val = coords[x][y];
    int left = y == 0 ? 10 : coords[x][y - 1];
    int right = y == CSIZE -1 ? 10: coords[x][y + 1];
    int up = x == 0 ? 10 : coords[x - 1][y];
    int down = x == CSIZE - 1 ? 10 : coords[x + 1][y];
    int ret = 0;
    if (val < up && val < down && val < left && val < right) {
        ret = val + 1;
    }
    return ret;
}

int Day9::basin(int x, int y)
{ 
    int val = coords[x][y];
    coords[x][y] = 10; //mark as visit
    if (val == 8) {
        return 1; //end recursion
    }
    int ret = 1;
    int left = y == 0 ? -10 : coords[x][y - 1];
    if (left > val && left < 9) ret += basin(x, y - 1);
    int right = y == CSIZE - 1 ? -10 : coords[x][y + 1];
    if (right > val && right <9) ret += basin(x, y + 1);
    int up = x == 0 ? -10 : coords[x - 1][y];
    if (up > val && up < 9) ret += basin(x - 1, y);
    int down = x == CSIZE - 1 ? -10 : coords[x + 1][y];
    if (down > val && down <9) ret += basin(x + 1, y);
    return ret;
}
