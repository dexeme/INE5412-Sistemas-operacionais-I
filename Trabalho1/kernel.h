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
        CPU cpu;
        Scheduler* scheduler;
        
    public:
        Kernel() {}
        Process create_process(ProcessParams params);
        void start(string scheduler_type);
        void save_context(Process processo);
        void restore_context(Process processo);
};

#endif