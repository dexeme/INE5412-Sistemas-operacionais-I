#include <iostream>
#include <fstream>
#include <string>

#include "file.h"
#include "process.h"
#include "scheduler.h"
#include "FCFS.cpp"
#include "SJF.cpp"
#include "CPU.h"

using namespace std;

CPU::CPU() {}
CPU::~CPU() {}

void CPU::save_context() {
    // Save the context of the current process
    // Save the PC, SP, ST and registers
}

void CPU::restore_context() {
    // Restore the context of the next process
    // Restore the PC, SP, ST and registers
}

void CPU::run_process() {
    // Run the process
    // Execute the instructions
}
