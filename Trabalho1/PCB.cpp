#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "PCB.h"

using namespace std;

PCB::PCB(int r, int sp, int pc, int st) {
    cout << "PCB criado" << endl;
    reg[6] = r;
    SP = sp;
    PC = pc;
    ST = st;
    running_time = 0;
    remaining_time = 0;
    finish_time = 0;
}

PCB::~PCB() {}

int PCB::get_reg(int reg) {}

int PCB::get_SP() {}

int PCB::get_PC() {}

int PCB::get_running_time() {}

int PCB::get_remaining_time() {}

int PCB::get_finish_time() {}
