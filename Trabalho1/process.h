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
    int getCreationTime() const;

    // Get running time
    int getRunningTime();

    // Set running time
    void setRunningTime(int time);

    // Get remaining time
    int getRemainingTime();

    // Set remaining time
    void setRemainingTime(int time);

	// Get duration
    int getDuration() const;

    // Set Duration
    void setDuration(int duration);

    // Get state
    int getState();

    // Set state
    void setState(ProcessState state);

	// Get priority
	int getPriority() const;

    // Get context
    Context* getContext();

    // Is finished
    bool is_finished();

    // Get current_quantum
    int getCurrentQuantum();

    // Set current_quantum
    void setCurrentQuantum(int quantum);

    int getFinishTime();

    void setFinishTime(int time);

    int getWaitingTime();

    void setWaitingTime(int time);

private:
    int pid;
    int creation_time;
    int duration;
    int priority;
    ProcessState state;
    int running_time;
    int remaining_time;
    int finish_time;
    int waiting_time;
    Context *context;
    int current_quantum;
};

#endif