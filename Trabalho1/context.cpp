#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "context.h"

using namespace std;

Context::Context(int r, int sp, int pc, int st) {
    cout << "context criado" << endl;
    reg[6] = r;
    SP = sp;
    PC = pc;
    ST = st;
}

Context::~Context() {}

int Context::get_reg(int reg) {}

int Context::get_SP() {}

int Context::get_PC() {}

int Context::get_ST() {}
