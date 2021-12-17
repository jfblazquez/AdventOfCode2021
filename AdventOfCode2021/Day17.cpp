#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
using namespace std;

#include "Day17.h"

Day17::Day17() {
    day = 17;
    filename = "input/Day17.txt";
    x1 = 185;
    x2 = 221;
    y1 = -74;
    y2 = -122;
    
    /*x1 = 20;
    x2 = 30;
    y1 = -5;
    y2 = -10;*/

}

int Day17::puzzle1() {
    int minXVel = (int)ceil(sqrt((2 * x1)+0.25) -0.5);
    int maxXVel = x2;
    int minYVel = y2;
    int maxYVel = -y2;

    amount = 0;
    int y = numeric_limits<int>::max();
    for (int sx = minXVel; sx <= maxXVel; sx++) {
        for (int sy = maxYVel; sy >= minYVel; sy--) {
            if (makeHit(sx, sy)) {
                if (y == numeric_limits<int>::max()) {
                    y = sy;                    
                }
                amount++;
            }
        }
    }    

    return (y*(y+1))/2;
}

int Day17::puzzle2() {
    if (amount == 0) {
        puzzle1();
    }
    return amount;
}

bool Day17::isHit(int x, int y)
{
    return x >= x1 && x <= x2 &&
        y <= y1 && y >= y2;
}

bool Day17::makeHit(int initialsx, int initialsy)
{
    int sx = initialsx;
    int sy = initialsy;
    int x = 0, y = 0;
    while (inRange(x, y)) {
        if (isHit(x, y)) return true;
        x += sx;
        y += sy;
        sx = sx > 0 ? sx - 1 : 0;
        sy--;
    }
    return false;
}

bool Day17::inRange(int x, int y)
{
    return x <= x2 && y >= y2;
}




