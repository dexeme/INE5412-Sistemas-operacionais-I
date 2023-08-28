#include <iostream>
#include <fstream>

#include "process.h"
#include "file.h"

using namespace std;

ProcessParams::ProcessParams(int c, int d, int p, int i) {
    creation_time = c;
    duration = d;
    priority = p;
    pid = i
    running_time = 0;
    finish_time = 0;
    state = 0; // 0 = criado e esperando (--), 1 = execução (##), 2 = acabou ou não começou (' ')
}

// Get pid
int ProcessParams::getPid() {
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

// Get finish time
int ProcessParams::getFinishTime() {
    return finish_time;
}

// Get duration
int ProcessParams::getDuration() {
    return duration;
}

// Get priority
int ProcessParams::getPriority() {
    return priority;
}


