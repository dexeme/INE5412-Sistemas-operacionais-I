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

void Kernel::start()
{
    cout << "KERNEL: Kernel iniciado\n"
         << endl;
    start_scheduler("SJF");
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
    return processo_novo;
}

void Kernel::create_scheduler(string scheduler_type)
{
    if (scheduler_type == "FCFS" || scheduler_type == "SJF") {
        cout << "KERNEL: Iniciando " << scheduler_type << "\n" << endl;
        ARM cpu = ARM();

        if (scheduler_type == "FCFS"){}

        else { scheduler = new SJF(cpu); }
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
