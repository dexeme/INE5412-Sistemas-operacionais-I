#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

class ProcessParams
{
public:
	ProcessParams(int c, int d, int p) {
		creation_time = c;
		duration = d;
		priority = p;
	}

private:	
	int creation_time; 
	int duration;
	int priority;
};