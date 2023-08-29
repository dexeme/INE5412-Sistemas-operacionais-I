#include <iostream>
#include <fstream>

#include "process.h"
#include "file.h"

using namespace std;

Process::Process(int c, int d, int p) {
    pid = i;
    creation_time = c;
    running_time = 0;
    remaining_time = duration;
    finish_time = 0;
    duration = d;
    priority = p;
}

// Get pid
int Process::getPid() const {
    return pid;
}

// Get creation time
int Process::getCreationTime() {
    return creation_time;
}

// Get running time
int Process::getRunningTime() {
    return running_time;
}

// Get remaining time
int Process::getRemainingTime() {
    return remaining_time;
}

void Process::setRemainingTime(int time)
{
    remaining_time = time;
}

// Get finish time
int Process::getFinishTime() {
    return finish_time;
}

// Get state
int Process::getState() {
    return state;
}

// Get duration
int Process::getDuration() const {
    return duration;
}

// Get priority
int Process::getPriority() {
    return priority;
}


