#ifndef CONTEXT_H
#define CONTEXT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;



class Context 
{
public:
    Context(int r, int sp, int pc, int st);
    ~Context();

    int get_reg(int reg);

    int get_SP();

    int get_PC();

    int get_ST();

private:
    int reg[6];
    int SP;
    int PC;
    int ST;
};

#endif