#pragma once
#include <bitset>
#include <vector>
#include <stack>
#include "BaseDay.h"
using namespace std;

class Packet {
public:
    int version;
    int typeId;
    long long literalValue;
    bool lengthTypeId;
    vector<Packet*> subpackets;
    Packet* parentPacket{};
    void calcResult();
    long long result;
};

enum class Status { version, type, lengthTypeId, literal, subPacketLength,endPacket, eof };

class Day16 : 
    public BaseDay {    
public:
    Day16();
    int puzzle1();
    int puzzle2();
private:
    int readPackets();
    int processVersion();
    int processType();
    bool processLengthTypeId();
    long long processLiteral();
    Status processEndPacket();
    int processSubPacketLength();    

    string bTransmission;
    vector<Packet*> packets;
    Packet* packet = nullptr; //current
    Packet* opPacket = nullptr; //current
    int posTransmission{};
    int posStack{};
    stack<int> stackPositions;
    stack<bool> stackByAmount; //true by amount, false by size
    stack<int> stackSubPackets;

};

