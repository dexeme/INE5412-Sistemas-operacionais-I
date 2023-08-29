#include <iostream>
#include <fstream>

#include "process.h"
#include "file.h"

using namespace std;

ProcessParams::ProcessParams(int c, int d, int p, int i) {
    pid = i;
    creation_time = c;
    running_time = 0;
    remaining_time = duration;
    finish_time = 0;
    state = ProcessState::PRONTO; // Inicia no estado pronto
    duration = d;
    priority = p;
}

// Get pid
int ProcessParams::getPid() const {
    return pid;
}

// Get creation time
int ProcessParams::getCreationTime() {
    return creation_time;
}

// Get running time
int ProcessParams::getRunningTime() {
    return running_time;
}

// Get remaining time
int ProcessParams::getRemainingTime() {
    return remaining_time;
}

void ProcessParams::setRemainingTime(int time)
{
    remaining_time = time;
}

// Get finish time
int ProcessParams::getFinishTime() {
    return finish_time;
}

// Get state
int ProcessParams::getState() {
    return state;
}

// Get duration
int ProcessParams::getDuration() const {
    return duration;
}

// Get priority
int ProcessParams::getPriority() {
    return priority;
}


