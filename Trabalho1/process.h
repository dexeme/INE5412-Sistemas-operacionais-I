#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <vector>

class ProcessParams
{
public:
	ProcessParams(int c, int d, int p, pid_t pid);

    // Get pid
    pid_t getPid();

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
    pid_t pid;
    int creation_time;
    int running_time;
    int finish_time;
    int duration;
    int state;
    int priority;
};

#endif