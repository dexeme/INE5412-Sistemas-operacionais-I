#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <vector>

#include "context.h"
#include "context.cpp"

enum ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    FINISHED
};

class Process
{
public:
	Process(int c, int d, int p, int i);

    // Get pid
    int getPid() const;

	// Get creation time
    int getCreationTime();

    // Get running time
    int getRunningTime();

    // Set running time
    void setRunningTime(int time);

    // Get remaining time
    int getRemainingTime();

    // Set remaining time
    void setRemainingTime(int time);

    // Get finish time
    int getFinishTime();

	// Get duration
    int getDuration();

    // Set Duration
    void setDuration(int duration);

    // Get state
    int getState();

    // Set state
    void setState(ProcessState state);

	// Get priority
	int getPriority();

    // Get context
    Context* getContext();

    // Is finished
    bool is_finished();

private:
    int pid;
    int creation_time;
    int duration;
    int priority;
    ProcessState state;
    int running_time;
    int remaining_time;
    int finish_time;
    Context *context;
};

#endif