#ifndef PROCESS_PARAMS_H
#define PROCESS_PARAMS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ProcessParams
{
private:
    ProcessParams();
    int creation_data;
    int duration;
    int priority;
    int pid;

public:
    ProcessParams(int creation_data, int duration, int priority, int pid) {
        this->creation_data = creation_data;
        this->duration = duration;
        this->priority = priority;
        this->pid = pid;
    }
    int get_creation_data() { return creation_data; }
    int get_duration() { return duration; }
    int get_priority() { return priority; }
    int get_pid() { return pid; }
};

#endif

