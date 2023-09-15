#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class RR : public Scheduler {
public:
    RR(CPU& _cpu) : Scheduler(_cpu) {}

    ~RR() {}

bool execute() {
    clear_finished_queue();
    CPU &cpu = get_cpu();
    queue<Process> &fila_de_prontos = get_ready_queue();
    queue<Process> &fila_de_executando = get_running_queue();

    if (fila_de_executando.empty()) {
        if (is_ready_queue_empty()) {
            return false;
        }
    }

    if (is_running_queue_empty()) {
        if (is_ready_queue_empty()) {
        }

        Process &proximo_processo = get_next_process();
        queue<Process> &running_queue = get_running_queue();
        queue<Process> &ready_queue = get_ready_queue();

        running_queue.push(proximo_processo);
        ready_queue.pop();

        set_running_queue(running_queue);
        set_ready_queue(ready_queue);

        auto [remaining_time, quantum_time] = cpu.run_process(fila_de_executando.front(), cpu); // Executa o próximo processo na CPU
        
        // Atualize o tempo restante do processo atual e o quantum
        fila_de_executando.front().setRemainingTime(remaining_time);
        fila_de_executando.front().setCurrentQuantum(quantum_time);
        
        if (remaining_time == 0) {
            finish_process(fila_de_executando.front()); // Se o processo terminou, finaliza ele
        }
        
        return true; // Continue a execução do escalonador
    }
    
    // Parte da preempção
    if (!is_ready_queue_empty()) {
        Process &proximo_processo = fila_de_prontos.front();
        int quantum_processo_atual = fila_de_executando.front().getCurrentQuantum();

        if (quantum_processo_atual == 2) { // Se o quantum expirou
            switch_process(fila_de_executando.front(), fila_de_prontos.front());

            // Zera o quantum do processo atual
            fila_de_executando.front().setCurrentQuantum(0);

            // Remove o processo atual da fila de execução e coloca-o na fila de prontos
            fila_de_prontos.push(fila_de_executando.front());
            fila_de_executando.push(proximo_processo);
            fila_de_prontos.pop();
            fila_de_executando.pop();
            set_running_queue(fila_de_executando);
            set_ready_queue(fila_de_prontos);
        }

        auto [remaining_time, quantum_time] = cpu.run_process(fila_de_executando.front(), cpu); // Executa o próximo processo na CPU
        
        // Atualize o tempo restante do processo atual e o quantum
        fila_de_executando.front().setRemainingTime(remaining_time);
        fila_de_executando.front().setCurrentQuantum(quantum_time);
        
        if (remaining_time == 0) {
            finish_process(fila_de_executando.front()); // Se o processo terminou, finaliza ele
        }

        return true; // Continue a execução do escalonador
    } else {
        // Se não houver preempção, execute apenas o processo atual
        auto [remaining_time, quantum_time] = cpu.run_process(fila_de_executando.front(), cpu);

        fila_de_executando.front().setRemainingTime(remaining_time);
        fila_de_executando.front().setCurrentQuantum(quantum_time);
        
        if (remaining_time == 0) {
            finish_process(fila_de_executando.front());
        }
    }
    
    return true;
}


    

    bool check_preemption(Process processo_atual) {} // TODO: Implementar preempção

};
