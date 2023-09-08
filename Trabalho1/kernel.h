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
        void start();
        void create_scheduler(string scheduler_type);
        Process create_process(ProcessParams p);
        void start_scheduler(string scheduler_type);
        void send_process(Process processo);
        void save_context(Process processo);
        void restore_context(Process processo);
};

#endif