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
    int total_context_changes;

public:


    Scheduler(CPU& _cpu) : cpu(_cpu), current_process(nullptr) {}

    int get_current_time() { return current_time; }

    int get_total_context_changes() { return total_context_changes; }

    void set_current_time(int time) { current_time = time; }

    bool is_ready_queue_empty() { return ready_queue.empty(); }

    bool is_running_queue_empty() { return running_queue.empty(); }

    queue<Process>& get_running_queue() { return running_queue; }

    queue<Process>& get_ready_to_print_info() { return ready_to_print_info; }

    void set_running_queue(queue<Process> running_queue) { this->running_queue = running_queue; }

    queue<Process>& get_finish_queue() { return finished_queue; }

    void clear_finished_queue() { finished_queue = queue<Process>(); }

    Process* get_current_process() { return current_process; }

    virtual bool execute() = 0;

    CPU& get_cpu() {return cpu;}

    queue<Process>& get_ready_queue() {return ready_queue;}
    void set_ready_queue(queue<Process> ready_queue) {this->ready_queue = ready_queue;}
    queue<Process> get_new_queue() {return new_queue;}


    // Remove o processo da fila de prontos e o coloca na fila de finalizados
    void finish_process(Process& processo) {
        total_context_changes++;
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



    // organiza a fila de prontos de acordo com o algoritmo de escalonamento
void organize_ready_queue(queue<Process>& ready_queue, unsigned int scheduler_type) {
    vector<Process> processos;
    
    // Transferir os processos da fila para o vetor
    while (!ready_queue.empty()) {
        processos.push_back(ready_queue.front());
        ready_queue.pop();
    }

    // Função de comparação personalizada para cada tipo de escalonamento
    auto compare_function = [](const Process& a, const Process& b, unsigned int scheduler_type) {
        switch (scheduler_type) {
            case 0: // Ordenar por ordem de chegada
                return a.getCreationTime() < b.getCreationTime();
            case 1: // Ordenar por duração (SJF)
                return a.getDuration() < b.getDuration();
            case 2: // Ordenar por prioridade (PREPRIO)
            case 3: // Ordenar por prioridade (PREPRIOD)
                return a.getPriority() > b.getPriority();
            default:
                return false;
        }
    };

    // Organizar o vetor com base no tipo de escalonamento
    sort(processos.begin(), processos.end(), [&](const Process& a, const Process& b) {
        return compare_function(a, b, scheduler_type);
    });

    // Transferir os processos de volta para a fila
    for (const Process& processo : processos) {
        ready_queue.push(processo);
    }
}





    void switch_process(Process& processo_atual, Process& processo_novo) {
        // Incrementa o número de trocas de contexto
        total_context_changes++;
        processo_novo.setState(RUNNING);
        processo_atual.setState(READY);
        processo_atual.setDuration(processo_atual.getRemainingTime());

    }
};

#endif