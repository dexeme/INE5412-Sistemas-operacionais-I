#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "process.h"
#include "scheduler.h"
#include "process_params.h"
#include "kernel.h"
#include "file.h"
#include "file.cc"



using namespace std;

void Kernel::start() {
    cout << "DEBUG: Kernel iniciado" << endl;
    File file;
    vector<ProcessParams> processes = file.read_file();
    }

void Kernel::create_process(ProcessParams params) {}