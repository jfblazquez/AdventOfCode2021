#pragma once
#include <vector>
#include "BaseDay.h"

class Points {
public:
    int p1{}, p2{}, p3{};
    Points(int cp1, int cp2, int cp3) : p1{ cp1 }, p2{ cp2 }, p3{ cp3 }{};
};

class Scanner {
public:
    int number{ -1 };
    vector<Points> points;
    vector<Points> pointsStatus;
    vector<Points> pointsRelative;
    
    int getStatus();
    void setStatus(int newStatus);
    void setRelativePos(Points newRelativePos);
private:
    int status{-1};
    Points relativePos{ -1,-1,-1 };
};


class Day19 : 
    public BaseDay {    
public:
    Day19();
    int puzzle1();
    int puzzle2();
private:
    void fillData();
    bool hasOverlapping(Scanner& scanner1, Scanner& scanner2, Points& relativePos);
    void setRelativePosition(Scanner& stationaryScanner, Scanner& unknownScanner);

    vector<Scanner> scanners;

};


