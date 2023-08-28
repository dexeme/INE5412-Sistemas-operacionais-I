#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <vector>

class ProcessParams
{
public:
	ProcessParams(int c, int d, int p, int pid);

    // Get pid
    int getPid();

	// Get creation time
    int getCreationTime();

    // Get running time
    int getRunningTime();

    // Get finish time
    int getFinishTime();

	// Get duration
    int getDuration();

    // Get state
    int getState();

	// Get priority
	int getPriority();

private:
    int pid;
    int creation_time;
    int running_time;
    int finish_time;
    int duration;
    int state;
    int priority;
};

#endif