#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>
using namespace std;

#include "Day20.h"

Day20::Day20() {
    day = 20;
    filename = "input/Day20.txt";
}

int Day20::puzzle1() {
    return launchEnhance(2);
}

int Day20::puzzle2() {
    return launchEnhance(50);
}

void Day20::fillData() {
    ifstream ifs(filename, ios::binary);
    string s;
    getline(ifs, s);
    for (int i = 0; i < 512; i++) {
        enhancement[i] = s[i] == '#';
    }

    image.clear();
    getline(ifs, s); //dummy
    while (getline(ifs, s)) {
        vector<bool> l;
        for (auto c : s) {
            l.push_back(c == '#');
        }
        image.push_back(l);
    }

}

int Day20::launchEnhance(int pass) {
    fillData();

    //printImage(image, "initial");
    //printImage(image, "expand");
    int totalPass = pass;
    expandImageSize(2 * totalPass);
    int ret = 0;
    for (int pass = 1; pass <= totalPass; pass++) {

        imageEn = image;
        auto xsize = image.size();
        auto ysize = image[0].size();
        for (int x = 0; x < xsize; x++) {
            for (int y = 0; y < ysize; y++) {
                enhance(x, y);
            }
        }
        removeBorders();

        ret = printImage(imageEn, "Enhance " + to_string(pass));
        image = imageEn;
    }

    return ret;
}

void Day20::expandImageSize(int size) {
    vector<bool> newLine;
    for (auto& line : image) {
        line.insert(line.begin(), size, false);
        line.insert(line.end(), size, false);
    }
    newLine.insert(newLine.begin(), 2*size + image.size(), false);
    image.insert(image.begin(), size, newLine);
    image.insert(image.end(), size, newLine);
}

void Day20::enhance(int x, int y) {
    int val = (getVal(x - 1, y - 1) << 8) + (getVal(x - 1, y) << 7) + (getVal(x - 1, y + 1) << 6) +
        (getVal(x, y - 1) << 5) + (getVal(x, y) << 4) + (getVal(x, y + 1) << 3) + 
        (getVal(x + 1, y - 1) << 2) + (getVal(x + 1, y) << 1) + (getVal(x + 1, y + 1) << 0);
    imageEn[x][y] = enhancement[val];
}

bool Day20::getVal(int x, int y) {
    if (x >= 0 && y >= 0 && x < image.size() && y < image[0].size()) {
        return image[x][y];
    }
    return false;
}

int Day20::printImage(vector<vector<bool>>& i, string text) {
    int count = 0;
    stringstream s;

    s << "printImage: " << text << endl;
    for (auto& row : i) {
        for (auto&& cell : row) {
            if (cell) {
                count++;
            }
            s << (cell ? '#' : '.');
        }
        s << '\n';
    }
    //cout << s.str();
    return count;
}

void Day20::removeBorders() {
    for (auto& row : imageEn) {
        row.erase(row.begin());
        row.erase(row.end() -1);
    }
    imageEn.erase(imageEn.begin());
    imageEn.erase(imageEn.end() -1);
}
