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
#include "RR.cpp"
#include "PRIO.cpp"
#include "PREPRIO.cpp"
#include "ARM.cpp"
#include "CPU.h"

using namespace std;

void Kernel::start()
{
    cout << "KERNEL: Kernel iniciado\n"
         << endl;
    start_scheduler("FCFS");
}

Process Kernel::create_process(ProcessParams params)
{
    int creation_data = params.get_creation_data();
    int priority = params.get_priority();
    int duration = params.get_duration();
    int pid = params.get_pid();

    Process processo_novo = Process(creation_data, duration, priority, pid);
    cout << "\nKERNEL: Criando processo " << pid << " | Duração: " << duration << "s" << endl;
    processo_novo.setRemainingTime(duration);
    processo_novo.setState(NEW);
    return processo_novo;
}

void Kernel::create_scheduler(string scheduler_type)
{
    if (scheduler_type == "FCFS" || scheduler_type == "SJF" || scheduler_type == "RR" || scheduler_type == "PRIO" || scheduler_type == "PREPRIO") 
    {
        cout << "KERNEL: Iniciando " << scheduler_type << "\n" << endl;
        ARM cpu = ARM();
        // TODO: Implementar criação de scheduler
        if (scheduler_type == "FCFS") { scheduler = new FCFS(cpu); }
        if (scheduler_type == "SJF") { scheduler = new SJF(cpu); }
        if (scheduler_type == "PRIO") { scheduler = new PRIO(cpu); }
        if (scheduler_type == "PREPRIO") { scheduler = new PREPRIO(cpu); }
        if (scheduler_type == "RR") { scheduler = new RR(cpu); }

    } else {
        cout << "KERNEL: Scheduler não reconhecido!" << endl;
        return;
    }
}

void Kernel::start_scheduler(string scheduler_type)
{
    create_scheduler(scheduler_type);
    bool running = true;
}

void Kernel::send_process(Process processo)
{
    scheduler->receive_process(processo);
}
