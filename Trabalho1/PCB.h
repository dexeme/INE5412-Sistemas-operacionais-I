#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;

enum ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

class PCB 
{
public:
    PCB(int r, int sp, int pc, int st, ProcessState processState);
    ~PCB();

    public:
        PCB() {}
        ~PCB() {}

    int get_reg(int reg);
    void set_reg(int reg, int value);

    int get_SP();
    void set_SP(int value);

    int get_PC();
    void set_PC(int value);

    int get_ST();
    void set_ST(int value);

        int get_ST();
        void set_ST(int value);
};

#endif