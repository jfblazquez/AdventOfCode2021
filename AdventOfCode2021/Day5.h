#pragma once
#include "BaseDay.h"

struct Point {
    int x{};
    int y{};
    Point(int cx, int cy) : x(cx), y(cy) {};

    bool operator< (const Point& rhs) const;
};

struct Line {
    Point p1;
    Point p2;
    bool isDiagonal();
    bool isHorizontal();
    bool isVertical();
    bool isValid(bool useDiagonal);
    Line(Point cp1, Point cp2) : p1(cp1), p2(cp2) {};
    Line(int x1,int y1,int x2,int y2) : p1(x1,y1), p2(x2,y2) {};
    vector<Point> points();
};

class Day5 : 
    public BaseDay {    
public:
    Day5();
    int puzzle1();
    int puzzle2();
    Line createLineFromFileLine(const string& line);
    int solve(bool useDiagonal);
};





