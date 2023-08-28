#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <vector>

class ProcessParams
{
public:
	ProcessParams(int c, int d, int p);

	// Get creation time
    int getCreationTime();

	// Get duration
    int getDuration();

	// Get priority
	int getPriority();

private:
    int creation_time;
    int duration;
    int priority;
};

#endif