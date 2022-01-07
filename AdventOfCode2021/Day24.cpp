#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <thread>
#include <map>
#include <execution>
#include "NotImplementedException.h"
using namespace std;

#include "Day24.h"

Day24::Day24() {
    day = 24;
    filename = "input/Day24.txt";
}

int Day24::puzzle1() {
    cout << "\n";
    ifstream ifs(filename);
    string op, a, b;
    while (ifs >> op) {
        ifs >> a;
        Instruction instruction;
        instruction.a = (regs)(a[0] - 'w');
        if (op[1] != 'n') { //inp has only one param
            ifs >> b;
            int opB = b[0] - 'w';
            if (opB >= 0 && opB <= 3) {
                instruction.b = opB;
                instruction.bAsReg = true;
            }
            else {
                instruction.b = std::stoi(b);
            }
        }

        switch (op[1]) {
        case 'n': //inp
            instruction.op = operation::inp;
            break;
        case 'd': //add
            instruction.op = operation::add;
            break;
        case 'u':
            instruction.op = operation::mul;
            break;
        case 'i':
            instruction.op = operation::div;
            break;
        case 'o':
            instruction.op = operation::mod;
            break;
        case 'q':
            instruction.op = operation::eql;
            break;
        default:
            throw 0;
        }

        instructions.push_back(std::move(instruction));
    }

    std::random_device rd;

    thread t1(&Day24::calc,this, "T1", std::mt19937(rd()));
    /*thread t2(&Day24::calc, this, "T2", std::mt19937(rd()));
    thread t3(&Day24::calc, this, "T3", std::mt19937(rd()));
    thread t4(&Day24::calc, this, "T4", std::mt19937(rd()));
    thread t5(&Day24::calc, this, "T5", std::mt19937(rd()));*/
    t1.join();
    /*t2.join();
    t3.join();
    t4.join();
    t5.join();*/
    
    /*cout << "result: ";
    for (int n : cpu.input) {
        cout << n;
    }
    cout << "\n";*/
    return 0;
}

int Day24::puzzle2() {
    throw NotImplementedException();
}

void Day24::decreaseInput(Cpu& cpu)
{
    int pos = 13;
    bool done = false;
    while (!done) {
        if (cpu.input[pos] != 1) {
            cpu.input[pos]--;
            done = true;
        }
        else
        {
            cpu.input[pos] = 9;
            pos--;
            if (pos < 0) {
                done = true;
            }
        }
    }
}

void Day24::decreaseRandom(Cpu& cpu, std::mt19937 &mt)
{
    
    for (int idx = 0;auto& n : cpu.input) {
        if (idx == 0) {
            n = 3; //may be between 38923612496639 and 40.... hope not...
            //n = dist34(mt);
        }
        else if (idx == 1) {
            n = 9;
        }
        else {
            n = dist19(mt);
        }
        idx++;
    }
}

void Day24::calc(string thread, std::mt19937 mt)
{

    bool first = true;
    Cpu* pcpu = new Cpu();
    Cpu& cpuInit = *pcpu;
    cpuInit.reset();
    cpuInit.input.fill(1);
    inputType inputMax;
    inputMax.fill(0);

    cpuInit.reset();
    //decreaseInput(cpu);
    if (first) {
        first = false;
        mtx.lock();
        cout << "Thread " << thread << " Starts with ";
        for (int n : cpuInit.input) {
            cout << n;
        }
        cout << "\n";
        mtx.unlock();
    }

    /*vector<Cpu> cpuTest{ Cpu(),Cpu(),Cpu() };
    cpuTest[0].input.fill(4);
    cpuTest[1].input.fill(9);
    cpuTest[2].input.fill(1);
    std::sort(cpuTest.begin(), cpuTest.end());*/
    vector<Cpu*> cpus = { pcpu };
    map <int, Cpu*> cpusByZ;

    for (int pc = 0;auto & instruction : instructions) {

        if (instruction.op == operation::inp) {
            for (Cpu* pcpu : cpus) {
                int regzz = pcpu->reg[z];
                auto&& find = cpusByZ.find(regzz);
                if (find == cpusByZ.end()) {
                    cpusByZ.insert(std::make_pair(regzz, pcpu));
                }
                else if (*pcpu < *find->second) {
                    delete find->second;
                    find->second = pcpu;
                }
                else {                    
                    delete pcpu;
                }
            }

            cpus.clear();

            for (auto& kvp : cpusByZ)
            {
                for (int i = 1; i <= 9; i++) {
                    Cpu* newCpu = new Cpu(*kvp.second);
                    newCpu->input[newCpu->inputPos] = i;
                    cpus.push_back(newCpu);
                }
                delete kvp.second;
            }
            cpusByZ.clear();

            size_t cpumb = (cpus.size() * (sizeof(Cpu) + sizeof(Cpu*)))/(1024*1024);
            cout << "New cpus: " << cpus.size() << " (" << cpumb << " MB) at PC: " << pc << "\n";
        }


        std::for_each(
            std::execution::par_unseq,
            cpus.begin(), cpus.end(), [&] (auto && item){
                item->execute(instruction);
            });
        /*for (Cpu* cpu : cpus) {
            cpu->execute(instruction);
        }*/
        pc++;
    }

    //locate bigger z == 0;
    std::sort(cpus.begin(), cpus.end(), [](Cpu* a, auto* b) { return *a < *b;});
    for (Cpu* pcpu : cpus) {
        Cpu& cpu = *pcpu;
        int regzz = cpu.reg[z];
        if (regzz == 0) {
            cout << "Found: ";
            for (int n : cpu.input) {
                cout << n;
            }
            cout << "\n";
            break;
        }
    }

    for (Cpu* pcpu : cpus) {
        delete pcpu;
    }

}

void Cpu::reset() {
    reg.fill(0);
    inputPos = 0;
}

void Cpu::execute(const Instruction& instruction)
{
    int bVal = instruction.bAsReg ? reg[instruction.b] : instruction.b;

    switch (instruction.op) {

    case operation::inp:
        reg[instruction.a] = inpOp();
        break;
    case operation::add:
        reg[instruction.a] += bVal;
        break;
    case operation::mul:
        reg[instruction.a] *= bVal;
        break;
    case operation::div:
        reg[instruction.a] /= bVal;
        break;
    case operation::mod:
        reg[instruction.a] %= bVal;
        break;
    case operation::eql:
        reg[instruction.a] = reg[instruction.a] == bVal ? 1 : 0;
        break;
    default:
        throw 0;
    }
}

void Cpu::print()
{
    cout << "w: " << reg[0]
        << " x: " << reg[1]
        << " y: " << reg[2]
        << " z: " << reg[3]
        << " inputPos " << inputPos << "\n";
}

bool Cpu::operator<(Cpu& rhs)
{
    inputType& l = this->input;
    inputType& r = rhs.input;
    for (int i = 0; i < 14; i++) {
        if (l[i] != r[i]) {
            return l > r; //for part 1
            //return l < r; //for part 2
        }
    }
    return true;

}
