#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "process.h"
#include "CPU.h"

using namespace std;

class Scheduler{
private:
    queue<Process> ready_queue;
    CPU& cpu;

protected:

    Process current_process = Process(0, 0, 0, 0);

public:


    Scheduler(CPU& _cpu) : cpu(_cpu) {}

    bool is_ready_queue_empty() {
        return ready_queue.empty();}

    void clear_ready_queue() {
        ready_queue = queue<Process>();}

    void add_process(Process process) {
        ready_queue.push(process);
    }

    virtual void execute() = 0;

    queue<Process> get_ready_queue() {return ready_queue;}

    void run_process(Process processo, CPU& cpu) {
        cout << "DEBUG: Processo " << processo.getPid() << " executando" << endl;
        cpu.run_process(processo);
    }

    // organiza a fila de prontos de acordo com o algoritmo de escalonamento
    virtual void organize_ready_queue() = 0;

    // retorna o processo que está na cabeça da fila de prontos
    Process get_next_process() {
        Process processo = ready_queue.front();
        ready_queue.pop();
        return processo;
    }

    void switch_process(Process processo_atual, Process processo_novo) {
        cout << "DEBUG: Trocando processo " << processo_atual.getPid() << " por processo " << processo_novo.getPid() << endl;
        cpu.save_context(processo_atual);
        cpu.restore_context(processo_novo);
    }
        

    
};

#endif
