#ifndef Kernel_H
#define Kernel_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "scheduler.h"
#include "process_params.h"

using namespace std;

class Kernel {
    private:
        Scheduler* scheduler;
    public:
        Kernel() {}
        Process* create_process(ProcessParams params);
        void start(string scheduler_type);
};

#endif