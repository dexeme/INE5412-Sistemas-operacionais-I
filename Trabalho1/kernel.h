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
        CPU* cpu;

    public:
        Scheduler* scheduler;

        Kernel() {}

        void start(unsigned int scheduler_type);
        
        Process create_process(ProcessParams p);

        void create_scheduler(unsigned int scheduler_type);
        void start_scheduler(unsigned int scheduler_type);
        void send_process(Process processo, unsigned int scheduler_type);

        
};

#endif