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
    cout << "KERNEL: Kernel iniciado\n" << endl;
    start_scheduler("SJF");
    }


    // for (unsigned int i = 0; i < processes_lidos.size(); i++) {
    //     ProcessParams p = processes_lidos[i];
    //     Process processo_novo = create_process(p);
    //     processos.push_back(processo_novo);
    //     cout << "DEBUG: Processo " << p.get_pid() << " criado" << endl;}
    // for (unsigned int i = 0; i < processos.size(); i++) {
    //     Process processo = processos[i];
    //     send_process(processo);
    //     cout << "DEBUG: Processo " << processo.getPid() << " enviado para o escalonador" << endl;
    // }

void Kernel::create_scheduler(string scheduler_type) {
    if (scheduler_type == "FCFS" || scheduler_type == "SJF") {
        cout << "KERNEL: Iniciando " << scheduler_type << "\n" << endl;
        ARM cpu = ARM();
        if (scheduler_type == "FCFS") {
            
        } else {
            scheduler = new SJF(cpu);
        }
        } else {
            cout << "KERNEL: Scheduler não reconhecido!" << endl;
            return;
        }

}

void Kernel::send_process(Process processo) {
    scheduler->add_process(processo);}

void Kernel::start_scheduler(string scheduler_type) {
    create_scheduler(scheduler_type);
    bool running = true;
}

Process Kernel::create_process(ProcessParams params) {
    int creation_data = params.get_creation_data();
    int priority = params.get_priority();
    int duration = params.get_duration();
    int pid = params.get_pid();

    Process processo_novo = Process(creation_data, duration, priority, pid);
    cout << "\nKERNEL: Criando processo " << pid << " | Duração: " << duration << "s" << endl;
    processo_novo.setRemainingTime(duration);
    return processo_novo;
    }

void Kernel::save_context(Process processo) {}

void Kernel::restore_context(Process processo) {}
