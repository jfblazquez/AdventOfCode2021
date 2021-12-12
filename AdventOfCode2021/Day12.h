#pragma once
#include <vector>
#include <functional>
#include "BaseDay.h"

class Node {
public:
    Node(string n);
    string name;
    vector<Node*> connections;
    bool isBig();
    bool isStart();
    bool isEnd();
};

class Day12 : 
    public BaseDay {    
public:
    Day12();    
    int puzzle1();
    void fillData();
    int puzzle2();
    Node* findOrCreate(string nodeName);
    void visitNode(Node&);
    void clearInfo();
    void printPath();
private:
    
    vector<Node*> nodes;
    vector<Node*> visit;
    int paths{};

    std::function<bool(Node *)> isFullVisit;
};

