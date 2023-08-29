#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <vector>


enum ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

class Process
{
public:
	Process(int c, int d, int p) {
        this->creation_time = c;
        this->duration = d;
        this->priority = p;
    }

    // Get pid
    int getPid() const;

	// Get creation time
    int getCreationTime();

    // Get running time
    int getRunningTime();

    // Get remaining time
    int getRemainingTime();

    // Set remaining time
    void setRemainingTime(int time);

    // Get finish time
    int getFinishTime();

	// Get duration
    int getDuration() const;

    // Get state
    int getState();

	// Get priority
	int getPriority();

private:
    int pid;
    int creation_time;
    int duration;
    int priority;
    ProcessState state;
    int running_time;
    int remaining_time;
    int finish_time;
};

#endif