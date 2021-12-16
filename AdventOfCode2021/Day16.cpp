#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "NotImplementedException.h"
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
    throw NotImplementedException();
}

int Day16::readPackets()
{
    ifstream ifs(filename, ios::binary);    
    string transmission;
    getline(ifs, transmission);
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
        switch (status)
        {
        case Status::version:
            //new packet
            packet = new Packet();
            versionSum += processVersion();
            status = Status::type;
            break;
        case Status::type:
            {bool literalPacket = processType() == 4;
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

int Day16::processVersion()
{
    constexpr int sizeVer = 3;
    string ver = bTransmission.substr(posTransmission, sizeVer);
    posTransmission += sizeVer;
    packet->version = stoi(ver, nullptr, 2);
    return packet->version;
}

int Day16::processType()
{
    constexpr int sizeType = 3;
    string type = bTransmission.substr(posTransmission, sizeType);
    posTransmission += sizeType;
    packet->typeId = stoi(type, nullptr, 2);
    return packet->typeId;
}

bool Day16::processLengthTypeId() {
    constexpr int sizeLti = 1;
    string lti = bTransmission.substr(posTransmission, sizeLti);
    posTransmission += sizeLti;
    packet->lengthTypeId = lti == "1";
    return packet->lengthTypeId;
}

long long Day16::processLiteral()
{
    bool haveNext = true;
    long long number{};
    while (haveNext) {
        number = number << 4;
        constexpr int sizeLiteral = 5;
        string subLiteral = bTransmission.substr(posTransmission, sizeLiteral);
        posTransmission += sizeLiteral;
        haveNext = subLiteral[0] == '1';
        number += stoi(subLiteral.substr(1,4), nullptr, 2);
    }
    packet->literalValue = number;
    return number;
}

Status Day16::processEndPacket()
{
    if (posTransmission + 11 /*min pkg size*/ < bTransmission.size()) {
        return Status::version;
    }
    else
    {
        return Status::eof;
    }
}

int Day16::processSubPacketLength()
{
    int spLength = 0;
    if (packet->lengthTypeId == false) {
        //15 bits total length
        constexpr int sizeSubLength = 15;
        string stringLength = bTransmission.substr(posTransmission, sizeSubLength);
        posTransmission += sizeSubLength;
        spLength = stoi(stringLength, nullptr, 2);
    }
    else
    {
        //11 bits amount of sub packets
        constexpr int sizeSubAmount = 11;
        string stringLength = bTransmission.substr(posTransmission, sizeSubAmount);
        posTransmission += sizeSubAmount;
        spLength = stoi(stringLength, nullptr, 2);
    }

    return spLength;
}
