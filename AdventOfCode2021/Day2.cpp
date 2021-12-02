#include <iostream>
#include <fstream>
using namespace std;

#include "Day2.h"

Day2::Day2() {
    day = 2;
    filename = "input/day2.txt";
}

int Day2::puzzle1() {
    ifstream ifs(filename, ios::binary);
    int inc = 0;
    int forward = 0;
    int depth = 0;
    while (!ifs.eof()) {
        string command;
        int move = 0;

        ifs >> command >> move;
        if (ifs.eof()) break;
        if (command == "forward") {
            forward += move;
        }
        else if (command == "up") {
            depth -= move;
        }
        else if (command == "down") {
            depth += move;
        }
    }

    int result = forward * depth;
    return result;
}

int Day2::puzzle2() {
    ifstream ifs(filename, ios::binary);
    int inc = 0;
    int forward = 0;
    int depth = 0;
    int aim = 0;
    while (!ifs.eof()) {
        string command;
        int move = 0;

        ifs >> command >> move;
        if (ifs.eof()) break;
        if (command == "forward") {
            forward += move;
            depth += move * aim;
        }
        else if (command == "up") {
            aim -= move;
        }
        else if (command == "down") {
            aim += move;
        }
    }

    int result = forward * depth;
    return result;
}
