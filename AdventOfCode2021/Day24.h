#pragma once
#include <array>
#include <random>
#include <mutex>
#include "BaseDay.h"

using inputType = array<unsigned char, 14>;

enum class operation {
    inp,add,mul,div,mod,eql,nop,neql,set
};

enum regs { w = 0, x, y, z };

class Instruction {
public:
    operation op{ operation::nop };
    regs a = w;
    int b{}; //reg or value
    bool bAsReg{};
};


class Cpu{
public:
    array <int, 4> reg{ 0,0,0,0 }; //w[0], x[1], y[2], z[3]
    inputType input;
    unsigned char inputPos{};
    int inpOp() {
        return input[inputPos++];
    }
    void reset();
    void execute(const Instruction& instruction);
    void print();
    bool operator< (Cpu& rhs);
};

class Day24 : 
    public BaseDay {    
public:
    Day24();
    int puzzle1();
    int puzzle2();
private:
    void decreaseInput(Cpu& cpu);
    void decreaseRandom(Cpu& cpu, std::mt19937& mt);
    void calc(string thread, std::mt19937 mt);
    void dynarec(vector<Instruction>& instructions);

    std::vector<Instruction> instructions;
    std::uniform_int_distribution<int> dist19{ 1, 9 };
    std::uniform_int_distribution<int> dist34{ 3, 4 };
    std::mutex mtx;

};

