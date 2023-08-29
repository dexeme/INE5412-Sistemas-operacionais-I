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
    for (unsigned int i = 0; i < processes.size(); i++) {
        ProcessParams p = processes[i];
        create_process(p);
    }
}

void Kernel::create_process(ProcessParams params) {
        int creation_data = params.get_creation_data();
        int priority = params.get_priority();
        int duration = params.get_duration();

        Process* processo_novo = new Process(creation_data, priority, duration);

        cout << "DEBUG: Criando processo " << params.get_creation_data() << endl;

        delete processo_novo;
    }
