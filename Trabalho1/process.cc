#include <iostream>
#include <fstream>

#include "file.h"
#include "process.h"

using namespace std;

ProcessParams::ProcessParams(int c, int d, int p) {
    creation_time = c;
    duration = d;
    priority = p;
}

// Get creation time
int ProcessParams::getCreationTime() {
    return creation_time;
}

// Get duration
int ProcessParams::getDuration() {
    return duration;
}

// Get priority
int ProcessParams::getPriority() {
    return priority;
}


