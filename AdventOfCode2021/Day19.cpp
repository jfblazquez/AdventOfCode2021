#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include "NotImplementedException.h"
using namespace std;

#include "Day19.h"

Day19::Day19() {
    day = 19;
    filename = "input/testDay19.txt";
}

void Day19::fillData() {
    ifstream ifs(filename, ios::binary);
    int p1, p2, p3;
    char dummychar;
    string line;
    Scanner currentScan;
    int scannerNumber = -1;
    while (getline(ifs, line))
    {
        if (line.substr(0,2) == "--") { //[0] == '-' fails with -\d
            if (currentScan.number >= 0) {
                currentScan.setStatus(0);
                scanners.push_back(currentScan);
            }
            currentScan = Scanner();
            currentScan.number = ++scannerNumber;
        }
        else if (!line.empty())
        {
            stringstream s(line);
            s >> p1 >> dummychar >> p2 >> dummychar >> p3;
            Points ps(p1, p2, p3);
            currentScan.points.push_back(ps);
        }
    }
    currentScan.setStatus(0);
    scanners.push_back(currentScan);
}
bool Day19::hasOverlapping(Scanner& scanner1, Scanner& scanner2, Points& relativePos)
{
    map<int, int> histogramDiff;

    for (auto& s1point : scanner1.pointsStatus) {
        for (auto& s2point : scanner2.pointsStatus) {
            int diff = s1point.p1 - s2point.p1; //sign may change
            histogramDiff[diff]++;
        }
    }

    map<int,int>::iterator x = std::max_element(histogramDiff.begin(), histogramDiff.end(),
        [](auto& p1, auto& p2) {
            return p1.second < p2.second; });

    bool overlapX = x->second >= 12;
    relativePos.p1 = x->first;

    histogramDiff.clear();

    for (auto& s1point : scanner1.pointsStatus) {
        for (auto& s2point : scanner2.pointsStatus) {
            int diff = s1point.p2 - s2point.p2; //sign may change
            histogramDiff[diff]++;
        }
    }

    auto y = std::max_element(histogramDiff.begin(), histogramDiff.end(),
        [](auto& p1, auto& p2) {
            return p1.second < p2.second; });

    bool overlapY = y->second >= 12;
    relativePos.p2 = y->first;

    histogramDiff.clear();

    for (auto& s1point : scanner1.pointsStatus) {
        for (auto& s2point : scanner2.pointsStatus) {
            int diff = s1point.p3 - s2point.p3; //sign may change
            histogramDiff[diff]++;
        }
    }

    auto z = std::max_element(histogramDiff.begin(), histogramDiff.end(),
        [](auto& p1, auto& p2) {
            return p1.second < p2.second; });

    bool overlapZ = z->second >= 12;
    relativePos.p3 = z->first;

    return overlapX && overlapY && overlapZ;
}
void Day19::setRelativePosition(Scanner& stationaryScanner, Scanner& unknownScanner)
{
    int status = 0;
    bool done = false;
    while (status < 8 && !done) {
        unknownScanner.setStatus(status);
        Points relativePos(0,0,0);
        done = hasOverlapping(stationaryScanner, unknownScanner, relativePos);
        if (done) {
            unknownScanner.setRelativePos(relativePos);
        }
        else
        {
            status++;
        }
    }
}

int Day19::puzzle1() {
    fillData();
    setRelativePosition(scanners[0], scanners[1]);
    setRelativePosition(scanners[1], scanners[4]);

    return 0;
}

int Day19::puzzle2() {
    throw NotImplementedException();
}

int Scanner::getStatus()
{
    return status;
}

void Scanner::setStatus(int newStatus)
{
    if (newStatus == status) return;
    // bit lsf to msf 
    // 12345678
    // xyz-----
    status = newStatus;
    pointsStatus.clear();
    for (auto& origPoint : points) {
        Points np(origPoint.p1, origPoint.p2, origPoint.p3);
        if (status & 1) {
            np.p1 *= -1;
        }
        if (status & 2) {
            np.p2 *= -1;
        }
        if (status & 4) {
            np.p3 *= -1;
        }
        pointsStatus.push_back(np);
    }
}

void Scanner::setRelativePos(Points newRelativePos)
{
    relativePos = newRelativePos;
    pointsRelative.clear();
    for (auto& statusPoint : pointsStatus) {
        pointsRelative.push_back(Points(
            statusPoint.p1 + relativePos.p1, 
            statusPoint.p2 + relativePos.p2, 
            statusPoint.p3 + relativePos.p3));
    }
}
