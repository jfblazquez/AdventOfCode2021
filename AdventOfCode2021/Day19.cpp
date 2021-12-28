#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <sstream>
#include <string>
using namespace std;

#include "Day19.h"

Day19::Day19() {
    day = 19;
    filename = "input/Day19.txt";
}

int Day19::puzzle1() {
    fillData();

    int relatives = 1;
    auto sizeScanners = scanners.size();
    for (auto s1idx = 0; s1idx < sizeScanners; s1idx++) {
        for (auto s2idx = 0; s2idx < sizeScanners; s2idx++) {
            auto& s1 = scanners[s1idx];
            auto& s2 = scanners[s2idx];
            if (s1.number != s2.number && s1.hasRelative && !s2.hasRelative) {
                bool newRelative = setRelativePosition(s1, s2);
                if (newRelative) {
                    relatives++;
                    //cout << "relatives: " << relatives << endl;
                    s1idx = 0;
                    s2idx = 0;
                }
            }
        }
    }

    set<Points> allPoints;
    for (auto& s : scanners) {
        for (Points& p : s.pointsRelative) {
            allPoints.insert(p);
        }
    }

    return allPoints.size();
}

int Day19::puzzle2() {
    if (scanners.size() == 0) puzzle1();
    int maxManhattan = 0;
    for (auto& s1 : scanners) {
        for (auto& s2 : scanners) {
            if (s1.number != s2.number) {
                int cManhattan = manhattan(s1.getRelativePos(), s2.getRelativePos());
                if (cManhattan > maxManhattan) {
                    maxManhattan = cManhattan;
                }
            }
        }
    }

    return maxManhattan;
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
        if (line.substr(0, 2) == "--") { //[0] == '-' fails with -\d
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
    scanners[0].setRelativePos(Points(0, 0, 0));
}

bool Day19::hasOverlapping(Scanner& scanner1, Scanner& scanner2, Points& relativePos) {
    map<int, int> histogramDiff;

    for (auto& s1point : scanner1.pointsStatus) {
        for (auto& s2point : scanner2.pointsStatus) {
            int diff = s1point.p1 - s2point.p1; //sign may change
            histogramDiff[diff]++;
        }
    }

    map<int, int>::iterator x = std::max_element(histogramDiff.begin(), histogramDiff.end(),
        [](auto& p1, auto& p2) {
            return p1.second < p2.second; });

    int maxOverlapX = x->second;
    bool overlapX = maxOverlapX >= 12;
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

    int maxOverlapY = y->second;
    bool overlapY = maxOverlapY >= 12;
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

    int maxOverlapZ = z->second;
    bool overlapZ = maxOverlapZ >= 12;
    relativePos.p3 = z->first;

    return overlapX && overlapY && overlapZ;
}
bool Day19::setRelativePosition(Scanner& stationaryScanner, Scanner& unknownScanner) {
    int status = 0;
    bool done = false;
    while (status < 24 && !done) {
        unknownScanner.setStatus(status);
        Points relativePos(0, 0, 0);
        done = hasOverlapping(stationaryScanner, unknownScanner, relativePos);
        if (done) {
            unknownScanner.setRelativePos(stationaryScanner.getRelativePos() + relativePos);
        }
        else
        {
            status++;
        }
    }
    return done;
}

int Day19::manhattan(const Points& p1, const Points& p2) {
    int m1 = (int)abs(p1.p1 - p2.p1);
    int m2 = (int)abs(p1.p2 - p2.p2);
    int m3 = (int)abs(p1.p3 - p2.p3);
    return m1 + m2 + m3;
}

void Scanner::setStatus(int newStatus) {
    if (newStatus == status) return;
    status = newStatus;
    pointsStatus.clear();
    for (auto& origPoint : points) {
        int x, y, z;
        switch (status) {
        case 0:
            x = origPoint.p1;
            y = origPoint.p2;
            z = origPoint.p3;
            break;
        case 1:
            x = origPoint.p1;
            y = -origPoint.p3;
            z = origPoint.p2;
            break;
        case 2:
            x = origPoint.p1;
            y = -origPoint.p2;
            z = -origPoint.p3;
            break;
        case 3:
            x = origPoint.p1;
            y = origPoint.p3;
            z = -origPoint.p2;
            break;
        case 4:
            x = -origPoint.p1;
            y = origPoint.p3;
            z = origPoint.p2;
            break;
        case 5:
            x = -origPoint.p1;
            y = -origPoint.p2;
            z = origPoint.p3;
            break;
        case 6:
            x = -origPoint.p1;
            y = -origPoint.p3;
            z = -origPoint.p2;
            break;
        case 7:
            x = -origPoint.p1;
            y = origPoint.p2;
            z = -origPoint.p3;
            break;
        case 8:
            x = origPoint.p2;
            y = origPoint.p1;
            z = -origPoint.p3;
            break;
        case 9:
            x = origPoint.p2;
            y = origPoint.p3;
            z = origPoint.p1;
            break;
        case 10:
            x = origPoint.p2;
            y = -origPoint.p1;
            z = origPoint.p3;
            break;
        case 11:
            x = origPoint.p2;
            y = -origPoint.p3;
            z = -origPoint.p1;
            break;
        case 12:
            x = -origPoint.p2;
            y = origPoint.p1;
            z = origPoint.p3;
            break;
        case 13:
            x = -origPoint.p2;
            y = -origPoint.p3;
            z = origPoint.p1;
            break;
        case 14:
            x = -origPoint.p2;
            y = -origPoint.p1;
            z = -origPoint.p3;
            break;
        case 15:
            x = -origPoint.p2;
            y = origPoint.p3;
            z = -origPoint.p1;
            break;
        case 16:
            x = origPoint.p3;
            y = origPoint.p1;
            z = origPoint.p2;
            break;
        case 17:
            x = origPoint.p3;
            y = -origPoint.p2;
            z = origPoint.p1;
            break;
        case 18:
            x = origPoint.p3;
            y = -origPoint.p1;
            z = -origPoint.p2;
            break;
        case 19:
            x = origPoint.p3;
            y = origPoint.p2;
            z = -origPoint.p1;
            break;
        case 20:
            x = -origPoint.p3;
            y = origPoint.p2;
            z = origPoint.p1;
            break;
        case 21:
            x = -origPoint.p3;
            y = -origPoint.p1;
            z = origPoint.p2;
            break;
        case 22:
            x = -origPoint.p3;
            y = -origPoint.p2;
            z = -origPoint.p1;
            break;
        case 23:
            x = -origPoint.p3;
            y = origPoint.p1;
            z = -origPoint.p2;
            break;


        default:
            cout << "NVV" << endl;
            throw(status);
        }

        Points np(x,y,z);
        pointsStatus.push_back(np);
    }
}

void Scanner::setRelativePos(Points newRelativePos) {
    hasRelative = true;
    relativePos = newRelativePos;
    pointsRelative.clear();
    for (auto& statusPoint : pointsStatus) {
        pointsRelative.push_back(Points(
            statusPoint.p1 + relativePos.p1, 
            statusPoint.p2 + relativePos.p2, 
            statusPoint.p3 + relativePos.p3));
    }
}

const Points& Scanner::getRelativePos() {
    return relativePos;
}

Points Points::operator+(const Points& other) const {
    return Points(p1 + other.p1,p2 + other.p2, p3 + other.p3);
}

bool Points::operator<(const Points& other) const {
    return p1 < other.p1 || 
        (p1 == other.p1 && p2 < other.p2) || 
        (p1 == other.p1 && p2 == other.p2 && p3 < other.p3);
}