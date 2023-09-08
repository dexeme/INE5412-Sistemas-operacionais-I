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
    Process current_process = Process(0, 0, 0, 99);
    CPU& cpu;


public:


    Scheduler(CPU& _cpu) : cpu(_cpu) {}

    bool is_ready_queue_empty() {
        return ready_queue.empty();}

    bool is_new_queue_empty() {
        return new_queue.empty();}

    void clear_ready_queue() {
        ready_queue = queue<Process>();}

    Process get_current_process() {
        return current_process;
    }


    void set_current_process(Process processo) {
        current_process = processo;}

    void add_process(Process process) {
        new_queue.push(process);
        cout << "DEBUG: Processo " << process.getPid() << " adicionado à fila de novos!" << endl;
        vector<Process> processos_organizados = organize_ready_queue(new_queue);
        clear_ready_queue();
        for (unsigned int i = 0; i < processos_organizados.size(); i++) {
            ready_queue.push(processos_organizados[i]);
            cout << "DEBUG: Processo " << processos_organizados[i].getPid() << " adicionado à fila de prontos!" << endl;
        }
    }

    virtual bool check_preemption(Process processo_atual) = 0;

    virtual bool execute() = 0;

    // pega a cpu
    CPU& get_cpu() {return cpu;}

    queue<Process> get_ready_queue() {return ready_queue;}
    void set_ready_queue(queue<Process> ready_queue) {this->ready_queue = ready_queue;}
    queue<Process> get_new_queue() {return new_queue;}

    void run_process(Process processo, CPU& cpu) {
        cout << "DEBUG: Processo " << processo.getPid() << " executando!" << endl;
        processo.setState(RUNNING);
        cout << "$DEBUG: Tempo restante do processo " << processo.getPid() << ": " << processo.getRemainingTime() << endl;
        processo.setRemainingTime(processo.getRemainingTime() - 1);
        cout << "*DEBUG: Tempo restante do processo " << processo.getPid() << ": " << processo.getRemainingTime() << endl;
    }

    // organiza a fila de prontos de acordo com o algoritmo de escalonamento
    virtual vector<Process> organize_ready_queue(queue<Process> new_queue) = 0;

    // retorna o processo que está na cabeça da fila de prontos
    Process get_next_process() {
        Process processo = ready_queue.front();}

    void switch_process(Process processo_atual, Process processo_novo) {
        cout << "DEBUG: Trocando processo " << processo_atual.getPid() << " por processo " << processo_novo.getPid() << endl;
        cpu.save_context(processo_atual);
        cpu.restore_context(processo_novo);
    }
        

    
};

#endif