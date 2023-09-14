#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "process.h"
#include "process.cpp"
#include "scheduler.h"
#include "process_params.h"
#include "kernel.h"
#include "file.h"
#include "file.cpp"
#include "FCFS.cpp"
#include "SJF.cpp"
#include "RR.cpp"
#include "PRIO.cpp"
#include "PREPRIO.cpp"
#include "ARM.cpp"
#include "CPU.h"
#include "output.cpp"

using namespace std;

void Kernel::start(unsigned int scheduler_type)
{
    cout << "KERNEL: Kernel iniciado\n"
         << endl;
    start_scheduler(scheduler_type);
}

Process Kernel::create_process(ProcessParams params)
{
    int creation_data = params.get_creation_data();
    int priority = params.get_priority();
    int duration = params.get_duration();
    int pid = params.get_pid();

    Process processo_novo = Process(creation_data, duration, priority, pid); // Cria um novo processo

    processo_novo.setRemainingTime(duration);
    processo_novo.setState(NEW);
    return processo_novo;
}

void Kernel::create_scheduler(unsigned int scheduler_type)
{
    string scheduler_name = "";

    if (scheduler_type == 0 || scheduler_type == 1 || scheduler_type == 2 || scheduler_type == 3 || scheduler_type == 4) 
    {

        ARM cpu = ARM();

        if (scheduler_type == 0) { scheduler = new FCFS(cpu); scheduler_name = "FCFS (First Come, First Served)"; }
        if (scheduler_type == 1) { scheduler = new SJF(cpu); scheduler_name = "Shortest Job First"; }
        if (scheduler_type == 2) { scheduler = new PRIO(cpu); scheduler_name = "Por prioridade, sem preempção"; }
        if (scheduler_type == 3) { scheduler = new PREPRIO(cpu); scheduler_name = "Por prioridade, com preempção por prioridade"; }
        if (scheduler_type == 4) { scheduler = new RR(cpu); scheduler_name = "Round-Robin"; }

        cout << "KERNEL: Iniciando " << scheduler_name << "\n" << endl;

    } else {
        cout << "KERNEL: Scheduler não reconhecido!" << endl;
        cout << "KERNEL: Os escalonadores disponíveis são: \n\n"
             <<         "0 - FCFS (First Come, First Served)\n"
             <<         "1 - SJF (Shortest Job First)\n"
             <<         "2 - PRIO (Por prioridade, sem preempção)\n"
             <<         "3 - PREPRIO (Por prioridade, com preempção por prioridade)\n"
             <<         "4 - RR (Round-Robin)\n"
                << endl;
        exit(1);
    }
}

void Kernel::start_scheduler(unsigned int scheduler_type)
{
    // Lê arquivo de entrada
    File file;
    file.read_file(); 
    vector<ProcessParams> process_params = file.get_processes();

    // Cria o escalonador
    create_scheduler(scheduler_type);

    // Indica se o sistema está ativo
    bool running = true;

    // Tempo atual do sistema
    int current_time = 0;

    int count = 0;

    // Classe responsável por imprimir os dados de saída
    Output output;
    output.print_header();

    while (running) // Enquanto o escalonador não terminar de executar todos os processos
    {
        for (ProcessParams process : process_params)
        {
            if (process.get_creation_data() == current_time) // Se o processo deve ser criado nesse tempo
            {
                Process new_process = create_process(process); // Cria o processo
                send_process(new_process, scheduler_type); // Envia o processo para o escalonador
            }
        }

        running = scheduler->execute(); // Executa o escalonador
        output.print_line(current_time, scheduler->get_running_queue(), scheduler->get_ready_queue(), scheduler->get_finish_queue()); // Imprime a linha da saída
        sleep(0.1); // Espera 1 segundo
        current_time++;
        scheduler->set_current_time(current_time); // Atualiza o tempo atual do escalonador
        count++;
        
    }
    output.print_process_information(scheduler->get_ready_to_print_info());

}

void Kernel::send_process(Process processo, unsigned int scheduler_type)
{
    scheduler->receive_process(processo, scheduler_type); // Envia o processo para o escalonador
}
