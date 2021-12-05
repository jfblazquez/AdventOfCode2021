#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <cmath>
using namespace std;

#include "Day5.h"

Day5::Day5() {
    day = 5;
    filename = "input/Day5.txt";
}

int Day5::puzzle1() {
    return solve(false);
}

int Day5::puzzle2() {

    return solve(true);
}

int Day5::solve(bool useDiagonal)
{
    ifstream ifs(filename, ios::binary);
    vector<Line> lines;
    for (std::string linefile; std::getline(ifs, linefile); ) {
        lines.emplace_back(createLineFromFileLine(linefile));
    }

    map<Point, int> waterMap;
    for (auto& line : lines) {
        if (line.isValid(useDiagonal)) {
            for (auto& point : line.points()) {
                auto it = waterMap.find(point);
                if (it != waterMap.end()) {
                    (*it).second++;
                }
                else {
                    waterMap[point] = 1;
                }

            }
        }
    }

    int result = 0;
    for (auto& kvp : waterMap) {
        if (kvp.second >= 2) result++;
    }
    return result;
}

Line Day5::createLineFromFileLine(const string& line) {
    //x1,y1 -> x2,y2
    string str = line;
    str.replace(str.find("->"), 2, ",");
    vector<int> vals;
    std::regex regexz(",");
    vector<string> list(sregex_token_iterator(str.begin(), str.end(), regexz, -1), sregex_token_iterator());
    std::for_each(list.begin(), list.end(), [&](string s) {vals.push_back(stoi(s));});
    return Line(vals[0], vals[1], vals[2], vals[3]);
}

bool Line::isDiagonal() {
    return p1.x != p2.x && p1.y != p2.y && abs(p1.x - p2.x) == abs(p1.y - p2.y);
}

bool Line::isHorizontal() {
    return p1.y == p2.y;
}

bool Line::isVertical() {
    return p1.x == p2.x;
}

vector<Point> Line::points() {
    vector<Point> p;    
    if (isHorizontal()) {
        for (int coord = (p1.x < p2.x ? p1.x : p2.x) ; coord <= (p1.x < p2.x ? p2.x : p1.x) ; coord++) {
            p.emplace_back(Point(coord, p1.y));
        }
    }
    else if (isVertical()) {
        for (int coord = (p1.y < p2.y ? p1.y : p2.y); coord <= (p1.y < p2.y ? p2.y : p1.y); coord++) {
            p.emplace_back(Point(p1.x, coord));
        }
    }
    else if (isDiagonal()) {
        //p1->p2
        int fx = p1.x < p2.x ? 1 : -1;
        int fy = p1.y < p2.y ? 1 : -1;
        int length = abs(p1.x - p2.x);
        for (int i = 0; i <= length; i++) {
            p.emplace_back(Point(p1.x + i*fx, p1.y + i*fy));
        }
    }
    return p;
}

bool Line::isValid(bool useDiagonal) {
    return isHorizontal() || isVertical() || (useDiagonal && isDiagonal());
}

bool Point::operator< (const Point& rhs) const {

    if (this->x < rhs.x) {
        return true;
    }
    else if (this->x == rhs.x && this->y < rhs.y) {
        return true;
    }

    return false;
}
