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
    queue<Process> ready_to_print_info;
    Process* current_process;
    CPU& cpu;
    int current_time;


public:


    Scheduler(CPU& _cpu) : cpu(_cpu), current_process(nullptr) {}

    int get_current_time() { return current_time; }

    void set_current_time(int time) { current_time = time; }

    void clear_ready_queue() { ready_queue = queue<Process>(); }

    void clear_running_queue() { running_queue = queue<Process>(); }

    bool is_ready_queue_empty() { return ready_queue.empty(); }

    bool is_running_queue_empty() { return running_queue.empty(); }

    bool is_new_queue_empty() { return new_queue.empty(); }

    queue<Process>& get_running_queue() { return running_queue; }

    queue<Process>& get_ready_to_print_info() { return ready_to_print_info; }

    void set_running_queue(queue<Process> running_queue) { this->running_queue = running_queue; }

    void set_current_process(Process* current_process) { this->current_process = current_process; }

    queue<Process>& get_finish_queue() { return finished_queue; }

    void clear_finished_queue() { finished_queue = queue<Process>(); }

    void set_finish_queue(queue<Process> finished_queue) { this->finished_queue = finished_queue; }

    Process* get_current_process() { return current_process; }




    // Remove o processo da fila de prontos e o coloca na fila de finalizados
    void finish_process(Process& processo) {
        processo.setState(FINISHED);
        processo.setFinishTime(get_current_time() - processo.getCreationTime()); // Define o tempo de término do processo
        finished_queue.push(processo); // Adiciona o processo na fila de finalizados
        ready_to_print_info.push(processo);
        running_queue.pop(); // Remove o processo da fila de executando
    }

    Process& get_next_process() {
        if (!ready_queue.empty()) {
            return ready_queue.front();
        } else {

        }
    }


    void receive_process(Process& process, unsigned int sched) {
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
    void organize_ready_queue(queue<Process>& ready_queue, unsigned int scheduler_type) {
        vector<Process> processos;
        
        // Transferir os processos da fila para o vetor
        while (!ready_queue.empty()) {
            processos.push_back(ready_queue.front());
            ready_queue.pop();
        }
        
        // Organizar o vetor com base no tipo de escalonamento
        if (scheduler_type == 0) {
            // Ordenar por ordem de chegada
            sort(processos.begin(), processos.end(), [](const Process& a, const Process& b) {
                return a.getCreationTime() < b.getCreationTime();
            });
        } else if (scheduler_type == 1) {
            // Ordenar por duração (SJF)
            sort(processos.begin(), processos.end(), [](const Process& a, const Process& b) {
                return a.getDuration() < b.getDuration();
            });
        } else if (scheduler_type == 2 || scheduler_type == 3) {
            // Ordenar por prioridade (PREPRIO ou PREPRIOD)
            sort(processos.begin(), processos.end(), [](const Process& a, const Process& b) {
                return a.getPriority() > b.getPriority();
            });
        }
        
        // Transferir os processos de volta para a fila
        for (const Process& processo : processos) {
            ready_queue.push(processo);
        }
    }





    void switch_process(Process& processo_atual, Process& processo_novo) {

        processo_novo.setState(RUNNING);
        processo_atual.setState(READY);
        processo_atual.setDuration(processo_atual.getRemainingTime());

    }
};

#endif