#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "PCB.h"

using namespace std;

PCB::PCB(int r, int sp, int pc, int st, ProcessState processState) {
    reg = reg;
    SP = sp;
    PC = pc;
    ST = st;
    state = processState;
    running_time = 0;
    remaining_time = duration;
    finish_time = 0;
}
