#include <iostream>
#include <fstream>

#include "process.h"
#include "file.h"
#include "context.h"

using namespace std;

Process::Process(int c, int d, int p, int i) {
    pid = i;
    creation_time = c;
    running_time = 0;
    remaining_time = d;
    finish_time = 0;
    duration = d;
    priority = p;
    state = ProcessState::NEW;
    context = new Context(0, 0, 0, 0);
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

// Set running time
void Process::setRunningTime(int time) {
    running_time = time;
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

// Set state
void Process::setState(ProcessState state) {
    this->state = state;
}

// Get duration
int Process::getDuration() {
    return duration;
}

// Set duration
void Process::setDuration(int duration) {
    this->duration = duration;
}

// Get priority
int Process::getPriority() {
    return priority;
}

// Get is finished
bool Process::is_finished() {
    return remaining_time = 0;
}


