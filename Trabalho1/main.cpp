#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "file.h"
#include "process.h"
#include "scheduler.h"
#include "INE5412.h"
#include "INE5412.cpp"

using namespace std;

int main() {
    INE5412 CPU;
    CPU.start("FCFS");

    return 0;
}
