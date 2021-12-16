#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

#include "Day16.h"

Day16::Day16() {
    day = 16;
    filename = "input/Day16.txt";
}

int Day16::puzzle1() {
    return readPackets();    
}

int Day16::puzzle2() {
    readPackets();
    cout << packet->result << endl;
    return numeric_limits<int>::max();
}

int Day16::readPackets() {
    posTransmission = 0;
    posStack = 0;
    ifstream ifs(filename, ios::binary);    
    string transmission;
    getline(ifs, transmission);
    //transmission = "C200B40A82"; // 3;
    //transmission = "04005AC33890"; //54
    //transmission = "880086C3E88112"; //7
    //transmission = "CE00C43D881120"; //9
    //transmission = "D8005AC2A8F0"; //1
    //transmission = "F600BC2D8F"; //0
    //transmission = "9C005AC2F8F0"; //0
    //transmission = "9C0141080250320F1802104A08"; //1;
    stringstream buffer;
    for (auto& c : transmission) {
        string cc;
        cc.push_back(c);
        std::bitset<4> bits(stoi(cc, nullptr, 16));
        buffer << bits;
    }

    bTransmission = buffer.str();
    int versionSum = 0;
    Status status = Status::version;

    while (status != Status::eof) {
        switch (status) {
        case Status::version:
            //new packet
            if (opPacket != nullptr) {
                Packet* p = new Packet();
                p->parentPacket = opPacket;
                opPacket->subpackets.push_back(p);
                packet = p;
            }
            else {
                packet = new Packet();
                opPacket = packet;
            }
            
            versionSum += processVersion();
            status = Status::type;
            break;
        case Status::type: {
            bool literalPacket = processType() == 4;
            if (literalPacket) {
                status = Status::literal;
            }
            else {
                status = Status::lengthTypeId;
            }
            }
            break;
        case Status::lengthTypeId:
            processLengthTypeId();
            status = Status::subPacketLength;
            break;
        case Status::literal:
            processLiteral();
            status = Status::endPacket;
            break;
        case Status::subPacketLength:
            processSubPacketLength();
            status = Status::version;
            break;
        case Status::endPacket:
            status = processEndPacket();
            break;
        case Status::eof:
        default:
            cout << "ERR" << endl;
            break;
        }
    }

    return versionSum;
}

int Day16::processVersion() {
    constexpr int sizeVer = 3;
    string ver = bTransmission.substr(posTransmission, sizeVer);
    posTransmission += sizeVer;
    posStack += sizeVer;
    packet->version = stoi(ver, nullptr, 2);
    return packet->version;
}

int Day16::processType() {
    constexpr int sizeType = 3;
    string type = bTransmission.substr(posTransmission, sizeType);
    posTransmission += sizeType;
    posStack += sizeType;
    packet->typeId = stoi(type, nullptr, 2);
    return packet->typeId;
}

bool Day16::processLengthTypeId() {
    constexpr int sizeLti = 1;
    string lti = bTransmission.substr(posTransmission, sizeLti);
    posTransmission += sizeLti;
    posStack += sizeLti;
    packet->lengthTypeId = lti == "1";
    return packet->lengthTypeId;
}

long long Day16::processLiteral() {
    bool haveNext = true;
    long long number{};
    while (haveNext) {
        number = number << 4;
        constexpr int sizeLiteral = 5;
        string subLiteral = bTransmission.substr(posTransmission, sizeLiteral);
        posTransmission += sizeLiteral;
        posStack += sizeLiteral;
        haveNext = subLiteral[0] == '1';
        number += stoi(subLiteral.substr(1,4), nullptr, 2);
    }
    packet->literalValue = number;
    return number;
}

Status Day16::processEndPacket() {
    Status ret = Status::version;
    packet->calcResult();
    if (opPacket == nullptr) return Status::eof;
    bool byAmount = stackByAmount.top();
    bool doPop = false;
    if (byAmount) {
        stackSubPackets.top()--;
        if (stackSubPackets.top() <= 0) {            
            doPop = true;
        }
    }
    else {
        int awaitSize = stackSubPackets.top();
        if (posStack == awaitSize) {

            doPop = true;
        }
    }

    if (doPop) {
        packet = opPacket;
        opPacket = opPacket->parentPacket;
        posStack += stackPositions.top();
        stackPositions.pop();
        stackSubPackets.pop();
        stackByAmount.pop();
        ret = Status::endPacket;
    }

    return ret;
}

int Day16::processSubPacketLength() {
    int spLength = 0;
    if (packet->lengthTypeId == false) {
        //15 bits total length
        constexpr int sizeSubLength = 15;
        string stringLength = bTransmission.substr(posTransmission, sizeSubLength);
        posTransmission += sizeSubLength;
        posStack += sizeSubLength;
        spLength = stoi(stringLength, nullptr, 2);
        stackByAmount.push(false);
    }
    else {
        //11 bits amount of sub packets
        constexpr int sizeSubAmount = 11;
        string stringLength = bTransmission.substr(posTransmission, sizeSubAmount);
        posTransmission += sizeSubAmount;
        posStack += sizeSubAmount;
        spLength = stoi(stringLength, nullptr, 2);
        stackByAmount.push(true);
    }

    stackSubPackets.push(spLength);
    stackPositions.push(posStack);
    posStack = 0;
    opPacket = packet;

    return spLength;
}

void Packet::calcResult() {
    switch (this->typeId) {
    case 0: //+
        for (auto& p : this->subpackets) {
            this->result += p->result;
        }
        break;
    case 1: //*
        this->result = 1;
        for (auto& p : this->subpackets) {
            this->result *= p->result;
        }
        break;
    case 2: //min
        this->result = numeric_limits<long long>::max();
        for (auto& p : this->subpackets) {
            this->result = this->result < p->result ? this->result : p->result;
        }
        break;
    case 3: //max
        this->result = numeric_limits<long long>::min();
        for (auto& p : this->subpackets) {
            this->result = this->result > p->result ? this->result : p->result;
        }
        break;
    case 4: //literal
        this->result = this->literalValue;
        break;
    case 5: //greater than
        this->result = subpackets[0]->result > subpackets[1]->result;
        break;
    case 6: //less than
        this->result = subpackets[0]->result < subpackets[1]->result;
        break;
    case 7: //equal to
        this->result = subpackets[0]->result == subpackets[1]->result;
        break;
    }
}
