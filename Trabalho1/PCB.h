#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;



class PCB 
{
public:
    PCB(int r, int sp, int pc, int st);
    ~PCB();

    int get_reg(int reg);

    int get_SP();

    int get_PC();

    int get_running_time();

    int get_remaining_time();

    int get_finish_time();


private:
    int reg[6];
    int SP;
    int PC;
    int ST;
    int running_time;
    int remaining_time;
    int finish_time;
};

#endif