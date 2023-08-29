#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "file.h"
#include "process.h"

using namespace std;

PCB::PCB() {}

PCB::~PCB() {}

ProcessState PCB::get_state() {}
void PCB::set_state(ProcessState state) {}

int PCB::get_reg(int reg) {}
void PCB::set_reg(int reg, int value) {}

int PCB::get_SP() {}
void PCB::set_SP(int value) {}

int PCB::get_PC() {}
void PCB::set_PC(int value) {}

int PCB::get_ST() {}
void PCB::set_ST(int value) {}

int PCB::get_running_time() {}
void PCB::set_running_time(int value) {}

int PCB::get_remaining_time() {}
void PCB::set_remaining_time(int value) {}

int PCB::get_finish_time() {}
void PCB::set_finish_time(int value) {}
