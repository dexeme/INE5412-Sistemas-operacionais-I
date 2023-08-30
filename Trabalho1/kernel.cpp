#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "process.h"
#include "process.cc"
#include "scheduler.h"
#include "process_params.h"
#include "kernel.h"
#include "file.h"
#include "file.cc"
#include "FCFS.cpp"
#include "SJF.cpp"
#include "PCB.h"
#include "PCB.cpp"



using namespace std;

void Kernel::start(string scheduler_type) {
    cout << "DEBUG: Kernel iniciado" << endl;
    vector<Process*> processos;
    File file;
    vector<ProcessParams> processes_lidos = file.read_file();
    for (unsigned int i = 0; i < processes_lidos.size(); i++) {
        ProcessParams p = processes_lidos[i];
        Process* processo_novo = create_process(p);
        processos.push_back(processo_novo);
        cout << "DEBUG: Processo " << p.get_pid() << " criado" << endl;
    }

    if (scheduler_type == "FCFS") {
        scheduler = new FCFS();

        cout << "DEBUG: Iniciando FCFS" << endl;


    } else if (scheduler_type == "SJF") {
        scheduler = new SJF();
        cout << "DEBUG: Iniciando SJF" << endl;


    } else {
        cout << "Scheduler não reconhecido!" << endl;
        return;
    }
}

Process* Kernel::create_process(ProcessParams params) {
    int creation_data = params.get_creation_data();
    int priority = params.get_priority();
    int duration = params.get_duration();
    int pid = params.get_pid();

    //PCB* pcb = new PCB();
    

    Process* processo_novo = new Process(creation_data, priority, duration, pid);

    cout << "DEBUG: Criando processo " << params.get_pid() << endl;

    // Adiciona o processo na fila de processos
    
    return processo_novo;
    }

void Kernel::save_context(Process processo) {}

void Kernel::restore_context(Process processo) {}