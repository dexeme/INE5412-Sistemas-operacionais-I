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
    queue<Process> new_queue;
    queue<Process> ready_queue;
    queue<Process> running_queue;
    queue<Process> finished_queue;
    Process* current_process;
    CPU& cpu;


public:


    Scheduler(CPU& _cpu) : cpu(_cpu), current_process(nullptr) {}

    void clear_ready_queue() { ready_queue = queue<Process>(); }

    void clear_running_queue() { running_queue = queue<Process>(); }

    bool is_ready_queue_empty() { return ready_queue.empty(); }

    bool is_running_queue_empty() { return running_queue.empty(); }

    bool is_new_queue_empty() { return new_queue.empty(); }

    queue<Process>& get_running_queue() { return running_queue; }

    void set_running_queue(queue<Process> running_queue) { this->running_queue = running_queue; }

    void set_current_process(Process* current_process) { this->current_process = current_process; }

    Process* get_current_process() { return current_process; }




    // Remove o processo da fila de prontos e o coloca na fila de finalizados
    void finish_process(Process& processo) {
        processo.setState(FINISHED);
        finished_queue.push(processo); // Adiciona o processo na fila de finalizados
        running_queue.pop(); // Remove o processo da fila de executando
    }

    Process& get_next_process() {
        if (!ready_queue.empty()) {

            return ready_queue.front();
        } else {
            // Lida com a situação em que a fila de prontos está vazia.
            // Isso pode envolver gerar um erro, lançar uma exceção ou tomar outra ação apropriada.
            // Neste exemplo, estamos lançando uma exceção para indicar a fila vazia.
            throw std::runtime_error("A fila de prontos está vazia.");
        }
    }


    void receive_process(Process& process, string sched) {
        process.setState(READY);
        process.setRemainingTime(process.getDuration());
        ready_queue.push(process);
        organize_ready_queue(ready_queue, sched);
    }

    virtual bool execute() = 0;

    // pega a cpu
    CPU& get_cpu() {return cpu;}

    queue<Process>& get_ready_queue() {return ready_queue;}
    void set_ready_queue(queue<Process> ready_queue) {this->ready_queue = ready_queue;}
    queue<Process> get_new_queue() {return new_queue;}

    // organiza a fila de prontos de acordo com o algoritmo de escalonamento
    void  organize_ready_queue(queue<Process> ready_queue, string scheduler_type) {
    vector<Process> processos;
    while (!ready_queue.empty()) {
        processos.push_back(ready_queue.front());
        ready_queue.pop();
    }
    if (scheduler_type == "FCFS") {
        // Ordena a fila de prontos por ordem de chegada
        sort(processos.begin(), processos.end(), [](Process a, Process b) {
            return a.getCreationTime() < b.getCreationTime();
        });
    }
    if (scheduler_type == "SJF") {
        // Ordena a fila de prontos por ordem de chegada
        sort(processos.begin(), processos.end(), [](Process a, Process b) {
            return a.getDuration() < b.getDuration();
        });
    }
    if (scheduler_type == "RR") {
        return;
    }
    if (scheduler_type == "PRIO") {
        // Ordena a fila de prontos por ordem de chegada
        sort(processos.begin(), processos.end(), [](Process a, Process b) {
            return a.getPriority() > b.getPriority();
        });
    }
    if (scheduler_type == "PREPRIO") {
        // Ordena a fila de prontos por ordem de chegada
        sort(processos.begin(), processos.end(), [](Process a, Process b) {
            return a.getPriority() > b.getPriority();
        });
    }
    for (Process processo : processos) {
        ready_queue.push(processo);
    }
    set_ready_queue(ready_queue);
    }



    void switch_process(Process& processo_atual, Process& processo_novo) {

        processo_novo.setState(RUNNING);
        processo_atual.setState(READY);
        processo_atual.setDuration(processo_atual.getRemainingTime());

    }
};

#endif