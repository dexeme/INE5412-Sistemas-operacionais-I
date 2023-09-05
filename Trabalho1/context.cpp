#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "context.h"

using namespace std;

Context::Context(int r, int sp, int pc, int st) {
    cout << "DEBUG: context criado" << endl;
    reg[6] = r;
    SP = sp;
    PC = pc;
    ST = st;
}

Context::~Context() {}

int Context::get_reg(int reg) {return this->reg[reg];}

int Context::get_SP() {return SP;}

int Context::get_PC() {return PC;}

int Context::get_ST() {return ST;}
