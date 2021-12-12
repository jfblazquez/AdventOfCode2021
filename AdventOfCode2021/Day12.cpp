#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

#include "Day12.h"

Day12::Day12() {
    day = 12;
    filename = "input/Day12.txt";
}

int Day12::puzzle1() {
    isFullVisit = [&](Node* n) -> bool {
        auto result = std::find_if(visit.begin(), visit.end(), [&](auto* node)
            {return node->name == n->name;});
        return result != visit.end();
    };
    fillData();
    Node& start = *findOrCreate("start");            
    visitNode(start);
    clearInfo();
    return paths;
}

int Day12::puzzle2() {
    paths = 0;

    isFullVisit = [&](Node* n) -> bool {
        if (n->name == "start") return true;
        bool hasSmallComplete = false;
        if (any_of(visit.begin(), visit.end(), [&](Node* nv) {
            if (nv->isBig()) return false;
            auto result = std::count_if(visit.begin(), visit.end(), [&](auto* node) {return node->name == nv->name;});
            return result > 1;
            })) {
            hasSmallComplete = true;
        }

        if (hasSmallComplete) {
            auto result = std::find_if(visit.begin(), visit.end(), [&](auto* node)
                {return node->name == n->name;});
            return result != visit.end();
        }
        return false;
    };

    fillData();
    Node& start = *findOrCreate("start");
    visitNode(start);
    clearInfo();
    return paths;
}

void Day12::fillData() {
    ifstream ifs(filename, ios::binary);
    string linefile;
    int ret = 0;
    int line = 0;

    while (getline(ifs, linefile)) {
        size_t possep = linefile.find('-');
        string node1name = linefile.substr(0, possep);
        string node2name = linefile.substr(possep + 1, linefile.length() - 1);
        Node* node1 = findOrCreate(node1name);
        Node* node2 = findOrCreate(node2name);
        node1->connections.push_back(node2);
        node2->connections.push_back(node1);
    }
}

Node* Day12::findOrCreate(string nodeName) {
    auto result = std::find_if(nodes.begin(), nodes.end(), 
        [&](auto node) -> bool {return node->name == nodeName;});
    if (result == nodes.end()) {
        nodes.push_back(new Node(nodeName));
        return *(nodes.end() - 1);
    }
    else {
        return *result;
    }
}

void Day12::visitNode(Node& currentNode) {
    if (currentNode.isEnd()) {
        paths++;
        printPath();
        return;
    }

    visit.push_back(&currentNode);
    for (Node* nc : currentNode.connections) {
        if (nc->isBig() || !isFullVisit(nc)) {            
            visitNode(*nc);
        }
    }
    visit.pop_back();
}

void Day12::clearInfo() {
    for_each(nodes.begin(), nodes.end(), [](auto n) {delete n;});
    nodes.clear();
}

void Day12::printPath() {
    return; //comment for debug
    cout << "path " << setw(2) << paths << " ";
    for (auto n : visit) {
        cout << n->name << "-";
    }
    cout << "end" << endl;
}

Node::Node(string n) {
    name = n;
}

bool Node::isBig() {
    return std::isupper((unsigned char) *name.begin());
}

bool Node::isStart() {
    return name == "start";
}

bool Node::isEnd() {
    return name == "end";
}
