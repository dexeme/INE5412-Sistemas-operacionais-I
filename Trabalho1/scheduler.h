#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "process.h"
#include "CPU.h"

using namespace std;

class Scheduler{
private:
    queue<Process> ready_queue;

public:
    void add_process(Process process) {
        ready_queue.push(process);
    } // recebe processos do kernel
    virtual void execute() = 0;

    queue<Process> get_ready_queue() {
        return ready_queue;}

        

    
};

#endif
