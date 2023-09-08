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
        Scheduler* scheduler;

    public:
        Kernel() {}
        void start();
        void start_scheduler(string scheduler_type);
        void create_processes();
        Process create_process(ProcessParams p);
        void save_context(Process processo);
        void restore_context(Process processo);
};

#endif