#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <cassert>
using namespace std;

#include "Day18.h"

Day18::Day18() {
    day = 18;
    filename = "input/Day18.txt";
}

int Day18::puzzle1() {

    //TODO: Clean memory
    testCases();

    ifstream ifs(filename, ios::binary);
    string exp;
    vector<Group*> groupsToSum;
    while (getline(ifs, exp)) {
        Group* group = Group::generateGroup(exp);
        assert(exp == group->print());
        groupsToSum.push_back(group);
    }

    //test
    int i = 1;
    for (auto& g : groupsToSum) {
        while (g->reduce());
        i++;
    }

    //sum
    Group* result = groupsToSum[0];
    for (int i = 1; i < groupsToSum.size(); i++) {
        result = new Group(result, groupsToSum[i]);
        while (result->reduce());
    }
    return result->magnitude();
}

int Day18::puzzle2() {

    ifstream ifs(filename, ios::binary);
    string exp;
    vector<Group*> groupsToSum;
    while (getline(ifs, exp)) {
        Group* group = Group::generateGroup(exp);
        assert(exp == group->print());
        groupsToSum.push_back(group);
    }

    //reduce Init
    int i = 1;
    for (auto& g : groupsToSum) {
        while (g->reduce());
        i++;
    }

    int maxMagnitude = 0;

    for (int ga = 0; ga < groupsToSum.size(); ga++) {
        for (int gb = 0; gb < groupsToSum.size(); gb++) {
            if (ga != gb) {
                auto result = new Group(groupsToSum[ga], groupsToSum[gb]);
                auto resultInverse = new Group(groupsToSum[gb], groupsToSum[ga]);
                while (result->reduce());
                while (resultInverse->reduce());
                auto magnitude = result->magnitude();
                auto magnitudeI = resultInverse->magnitude();
                if (magnitude > maxMagnitude) {
                    maxMagnitude = magnitude;
                }
                if (magnitudeI > maxMagnitude) {
                    maxMagnitude = magnitudeI;
                }
            }
        }
    }

    return maxMagnitude;

}

Group* Group::generateGroup(string exp) {
    string number;
    Group* gc{};

    for (char& c : exp) {
        if (c == '[') {
            Group* g = new Group(gc);
            if (gc) {
                if (gc->isLeftEmpty()) {
                    gc->groupL = g;
                }
                else {
                    gc->groupR = g;
                }
            }
            gc = g;
        }
        else if (c == ']') {
            if (number.size()) {
                gc->regularR = stoi(number);
                number.clear();
            }
            if (!gc->parent) break;
            gc = gc->parent;
        }
        else if (c == ',') {
            if (number.size()) {
                gc->regularL = stoi(number);
                number.clear();
            }
        }
        else { //number
            number.push_back(c);
        }
    }

    return gc;
}


void Day18::testCases() {
    //Check read
    string exp = "[[6,[5,[4,[3,2]]]],1]";
    string result = "[[6,[5,[4,[3,2]]]],1]";
    Group* group = Group::generateGroup(exp);
    assert(result == group->print());

    //check reduce
    //test 1
    exp = "[[[[[9,8],1],2],3],4]";
    result = "[[[[0,9],2],3],4]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 2
    exp = "[7,[6,[5,[4,[3,2]]]]]";
    result = "[7,[6,[5,[7,0]]]]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 3
    exp = "[[6,[5,[4,[3,2]]]],1]";
    result = "[[6,[5,[7,0]]],3]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 4
    exp = "[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]";
    result = "[[3,[2,[8,0]]],[9,[5,[7,0]]]]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 5
    exp = "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]";
    result = "[[3,[2,[8,0]]],[9,[5,[7,0]]]]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 6
    exp = "[[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]";
    result = "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]";
    group = Group::generateGroup(exp);
    while (group->reduce()); /*{
        cout << group->print() << endl;
    }*/
    assert(result == group->print());
    
    //test magnitude
    //test 7
    exp = "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]";
    int magnitude = 3488;
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(magnitude == group->magnitude());

    //test8
    exp = "[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]";
    magnitude = 4140;
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(magnitude == group->magnitude());

    //test 9
    exp = "[[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]],[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]]";
    result = "[[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());        

    //test11
    exp = "[[[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]],[7,[5,[[3,8],[1,4]]]]]";
    result = "[[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 12
    exp = "[[[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]],[[2,[2,2]],[8,[8,1]]]]";
    result = "[[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 13
    exp = "[[[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]],[2,9]]";
    result = "[[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 14
    exp = "[[[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]],[1,[[[9,3],9],[[9,0],[0,7]]]]]";
    result = "[[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 15
    exp = "[[[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]],[[[5,[7,4]],7],1]]";
    result = "[[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 16
    exp = "[[[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]],[[[[4,2],2],6],[8,7]]]";
    result = "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]";
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());

    //test 17 part2
    exp = "[[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]],[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]]";
    result = "[[[[7,8],[6,6]],[[6,0],[7,7]]],[[[7,8],[8,8]],[[7,9],[0,6]]]]";
    magnitude = 3993;
    group = Group::generateGroup(exp);
    while (group->reduce());
    assert(result == group->print());
    assert(magnitude == group->magnitude());
}

bool Group::isLeft() {
    return parent && parent->groupL == this;
}

bool Group::isRight() {
    return parent && parent->groupR == this;
}

bool Group::isLeftEmpty() {
    return regularL == NOVAL && nullptr == groupL;
}

int Group::magnitude() {
    int mL = regularL == NOVAL ? groupL->magnitude() :  regularL;
    int mR = regularR == NOVAL ? groupR->magnitude() : regularR;
    int m = (3 * mL) + (2 * mR);
    return m;
}

string Group::print() {
    stringstream s;
    s << '[';
    if (groupL) {
        s << groupL->print();
    }
    else {
        s << regularL;
    }
    s << ',';
    if (groupR) {
        s << groupR->print();
    }
    else {
        s << regularR;
    }
    s << ']';
    return string(s.str());
}

string Group::printLevel(int level) {
    stringstream s;
    s << level;
    if (groupL) {
        s << groupL->printLevel(level + 1);
    }
    else {
        s << ' ';
        if (regularL >= 10) s << ' ';
        if (regularL >= 100) s << ' ';
        if (regularL >= 1000) s << ' ';
    }
    s << ',';
    if (groupR) {
        s << groupR->printLevel(level + 1);
    }
    else {
        s << ' ';
        if (regularR >= 10) s << ' ';
        if (regularR >= 100) s << ' ';
        if (regularR >= 1000) s << ' ';
    }
    s << level;
    return string(s.str());
}

bool Group::reduce(bool verbose) {
    string originalLevels = printLevel();
    bool isExplode = false;
    bool isSplit = false;
    bool ret = explode(1);
    isExplode = ret;
        
    if (!ret) {
        ret = split(1);
        isSplit = ret;
    }
    if (ret && verbose)
    {
        cout << print();
        if (isExplode) {
            cout << "   (explode)" << endl;
        }
        if (isSplit) {
            cout << "   (split)" << endl;   
            assert(originalLevels.find('5') == string::npos);
        }
        cout << printLevel() << endl;        
    }

    return ret;
}

bool Group::explode(int depth) {
    bool ret = false;
    if (depth > 4) {
        assert(nullptr == groupL);
        assert(nullptr == groupR);
        if (isLeft()) {
            //look for parent where im right
            auto p = this->parent;
            while (p && p->isLeft()) {
                p = p->parent;
            }
            p = p->parent;

            int* numberLeft{};
            if (p) {
                //now go from left till im regular
                if (!p->groupL) {
                    numberLeft = &p->regularL;
                }
                else
                {
                    p = p->groupL;
                    while (p->groupR) {
                        p = p->groupR;
                    }
                    numberLeft = &p->regularR;
                }
            }

            if (numberLeft) {
                *numberLeft += this->regularL;
            }

            //numberRight
            int* numberRight{};
            p = parent;
            if (!p->groupR) {
                numberRight = &p->regularR;
            }
            else
            {
                p = p->groupR;
                while (p->groupL) {
                    p = p->groupL;
                }
                numberRight = &p->regularL;
            }

            *numberRight += this->regularR;

            parent->groupL = nullptr;
            parent->regularL = 0;
            delete this;
        }
        else {
            //look for parent where im left
            auto p = this->parent;
            while (p && p->isRight()) {
                p = p->parent;
            }
            p = p->parent;

            int* numberRight{};
            if (p) {
                //now go from right till im regular
                if (!p->groupR) {
                    numberRight = &p->regularR;
                }
                else
                {
                    p = p->groupR;
                    while (p->groupL) {
                        p = p->groupL;
                    }
                    numberRight = &p->regularL;
                }
            }

            if (numberRight) {
                *numberRight += this->regularR;
            }

            //numberLeft
            int* numberLeft{};
            p = parent;
            if (!p->groupL) {
                numberLeft = &p->regularL;
            }
            else
            {
                p = p->groupL;
                while (p->groupR) {
                    p = p->groupR;
                }
                numberLeft = &p->regularR;
            }

            *numberLeft += this->regularL;

            parent->groupR = nullptr;
            parent->regularR = 0;
            delete this;
        }

        ret = true;
    }
    if (!ret && groupL) {
        ret = groupL->explode(depth + 1);
    }
    if (!ret && groupR) {
        ret = groupR->explode(depth + 1);
    }

    return ret;
}

bool Group::split(int depth) {
    bool ret = false;
    if (!ret && regularL != NOVAL && regularL >= 10) {
        ret = true;
        groupL = new Group(regularL >> 1, (regularL >> 1) + (regularL % 2), this);
        regularL = NOVAL;
    }

    if (!ret && groupL) {
        ret = groupL->split(depth + 1);
    }

    if (!ret && regularR != NOVAL && regularR >= 10) {
        ret = true;
        groupR = new Group(regularR >> 1, (regularR >> 1) + (regularR % 2), this);
        regularR = NOVAL;
    }

    if (!ret && groupR) {
        ret = groupR->split(depth + 1);
    }

    return ret;
}