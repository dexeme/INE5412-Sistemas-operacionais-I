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
#include "ARM.cpp"
#include "CPU.h"



using namespace std;

void Kernel::start() {
    cout << "DEBUG: Kernel iniciado" << endl;
    create_processes();
    start_scheduler("SJF");}

void Kernel::create_processes() {
    vector<Process> processos;
    File file;
    vector<ProcessParams> processes_lidos = file.read_file();
    for (unsigned int i = 0; i < processes_lidos.size(); i++) {
        ProcessParams p = processes_lidos[i];
        Process processo_novo = create_process(p);
        processos.push_back(processo_novo);
        cout << "DEBUG: Processo " << p.get_pid() << " criado" << endl;
    }
    
}

void Kernel::start_scheduler(string scheduler_type) {
    Scheduler* scheduler = nullptr;
    if (scheduler_type == "FCFS") {
        cout << "DEBUG: Iniciando FCFS" << endl;
        ARM cpu = ARM();
        scheduler = new FCFS(cpu);

    } else if (scheduler_type == "SJF") {
        cout << "DEBUG: Iniciando SJF" << endl;
        ARM cpu = ARM();
        scheduler = new SJF(cpu);

        for (unsigned int i = 0; i < processos.size(); i++) {
            cout << "DEBUG: Processo " << processos[i].getPid() << " adicionado ao escalonador" << endl;
            scheduler->add_process(processos[i]);
            scheduler->organize_ready_queue();
        }
        } else {
            cout << "Scheduler não reconhecido!" << endl;
            return;
        }
}

Process Kernel::create_process(ProcessParams params) {
    int creation_data = params.get_creation_data();
    int priority = params.get_priority();
    int duration = params.get_duration();
    int pid = params.get_pid();

    Process processo_novo = Process(creation_data, duration, priority, pid);

    cout << "DEBUG: Criando processo " << pid << endl;
    
    return processo_novo;
    }

void Kernel::save_context(Process processo) {}

void Kernel::restore_context(Process processo) {}