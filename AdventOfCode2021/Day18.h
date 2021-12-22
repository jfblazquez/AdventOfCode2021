#pragma once
#include "BaseDay.h"

#define NOVAL numeric_limits<int>::max()

class Group {
public:


    Group(Group* g) : parent(g) {};
    Group(Group* gL, Group* gR) : groupL{ gL }, groupR{ gR } {
        groupL->parent = this;
        groupR->parent = this;
    };
    Group(int rL, int rR, Group* cparent) : regularL(rL), regularR{ rR }, parent{ cparent } {};

    Group* groupL{};
    Group* groupR{};
    Group* parent{};

    bool isLeft();
    bool isRight();
    
    int regularL{ NOVAL };
    int regularR{ NOVAL };
    void sum(int val, bool left);

    bool isLeftEmpty();
    bool reduce();
    bool explode(int depth);
    bool split(int depth);
    int magnitude();
    string print();
    string printLevel(int level = 1);

};

class Day18 : 
    public BaseDay {    
public:
    Day18();
    int puzzle1();    
    int puzzle2();
    void testCases();
private:
    Group* generateGroup(string exp);
};

