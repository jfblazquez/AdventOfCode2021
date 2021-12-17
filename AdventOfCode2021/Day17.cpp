#include <iostream>
#include <fstream>
#include <cmath>
#include "NotImplementedException.h"
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
    int maxXVel = minXVel; //x2 /2
    while (hitxTarget(maxXVel + 1)) {
        maxXVel++;
    }

    bool minYFound = false;
    int minYVel = 0; 
    int maxYVel = 0;
    for (int yRange = 0; yRange < 1000; yRange++) {

        if (!minYFound && hityTarget(yRange)) {
            minYFound = true;
            minYVel = 0;
        }
        else if (minYFound && hityTarget(yRange)) {
            maxYVel = yRange;
            
        }
    }

    int y = 0;
    bool done = false;
    for (int sx = minXVel;!done && sx <= maxXVel; sx++) {
        for (int sy = maxYVel;!done && sy >= minYVel; sy--) {
            if (makeHit(sx, sy)) {
                y = sy;
                done = true;
            }
        }
    }    

    return (y*(y+1))/2;
}

int Day17::puzzle2() {
    throw NotImplementedException();
}

bool Day17::hitxTarget(int initialSpeed)
{
    int speed = initialSpeed;
    int val = 0;
    while (val < x1 && speed >= 0) {
        val += speed;
        speed--;        
    }
    return val >= x1 && val <= x2;
}

bool Day17::hityTarget(int initialSpeed)
{
    int speed = initialSpeed;
    int val = 0;
    while (val > y1) {
        val += speed;
        speed--;
    }
    return val <= y1 && val >= y2;
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




