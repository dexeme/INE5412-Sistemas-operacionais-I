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

class PCB {
    private:
        int reg[6];
        int SP;
        int PC;
        int ST;
        ProcessState state;
        int running_time;
        int remaining_time;
        int finish_time;

    public:
        PCB();
        ~PCB();

        ProcessState get_state();
        void set_state(ProcessState state);

        int get_reg(int reg);
        void set_reg(int reg, int value);

        int get_SP();
        void set_SP(int value);

        int get_PC();
        void set_PC(int value);

        int get_ST();
        void set_ST(int value);

        int get_running_time();
        void set_running_time(int value);

        int get_remaining_time();
        void set_remaining_time(int value);

        int get_finish_time();
        void set_finish_time(int value);
};

#endif