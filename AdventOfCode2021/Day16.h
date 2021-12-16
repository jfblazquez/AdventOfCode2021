#pragma once
#include <bitset>
#include <vector>
#include "BaseDay.h"
using namespace std;

class Packet {
public:
    int version;
    int typeId;
    long long literalValue;
    bool lengthTypeId;
    vector<Packet*> subpackets;
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
    int posTransmission{};
};

