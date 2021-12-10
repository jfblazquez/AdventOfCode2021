#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

#include "Day10.h"

Day10::Day10() {
    day = 10;
    filename = "input/Day10.txt";
}

int Day10::puzzle1() {
    ifstream ifs(filename, ios::binary);
    string linefile;
    int ret = 0;
    while (getline(ifs, linefile)) {
        ret += ilegalPoints(linefile);                
    }
    return ret;
}

int Day10::puzzle2() {
    ifstream ifs(filename, ios::binary);
    string linefile;
    int ret = 0;
    vector<long long> closeChunkPoints;
    while (getline(ifs, linefile)) {
        if (!ilegalPoints(linefile)) {
            closeChunkPoints.push_back(closePoints(linefile));
        }        
    }

    sort(closeChunkPoints.begin(), closeChunkPoints.end());
    size_t pos = closeChunkPoints.size() >> 1;

    cout << "Day 6 puzzle 2: " << closeChunkPoints[pos] << endl;
    return std::numeric_limits<int>::max();
}

int Day10::ilegalPoints(string& linefile) {
    stack<char> chunk;
    char open{};
    for (auto& c : linefile) {
        switch (c) {
        case '(':
        case '[':
        case '{':
        case '<':
            chunk.push(c);
            break;
        case ')':
            open = topandpop(chunk);
            if (open != '(') return 3;
            break;
        case ']':
            open = topandpop(chunk);
            if (open != '[') return 57;
            break;
        case '}':
            open = topandpop(chunk);
            if (open != '{') return 1197;
            break;
        case '>':
            open = topandpop(chunk);
            if (open != '<') return 25137;
            break;
        }
    }
    return 0;
}

char Day10::topandpop(stack<char>& s)
{
    char ret = s.top();
    s.pop();
    return ret;
}

long long Day10::closePoints(string& linefile) {
    stack<char> chunk;
    char open{};
    for (auto& c : linefile) {
        switch (c) {
        case '(':
        case '[':
        case '{':
        case '<':
            chunk.push(c);
            break;
        case ')':
        case ']':
        case '}':
        case '>':
            open = chunk.top();
            chunk.pop();
            break;
        }
    }

    long long ret = 0;
    while (chunk.size()) {
        ret *= 5;
        char c = topandpop(chunk);
        switch (c) {
        case '(':
            ret += 1;
            break;
        case '[':
            ret += 2;
            break;
        case '{':
            ret += 3;
            break;
        case '<':
            ret += 4;
            break;
        }
    }

    return ret;
}

