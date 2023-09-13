#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>

using namespace std;

class SJF : public Scheduler {
public:
    SJF(CPU& _cpu) : Scheduler(_cpu) {}

    ~SJF() {}

bool execute() {

    queue<Process>& fila_de_executando = get_running_queue();
    queue<Process>& fila_de_prontos = get_ready_queue();
    CPU &cpu = get_cpu();

    if (!is_running_queue_empty()) {
        if (is_ready_queue_empty()) {
        }
    }
    if (is_running_queue_empty()) { // Se o processo atual é nulo
        if (is_ready_queue_empty()) {
            return false;
        }
        int prioridade_atual = fila_de_executando.front().getPriority();

        Process& proximo_processo = get_next_process();
        queue<Process>& running_queue = get_running_queue();
        queue<Process>& ready_queue = get_ready_queue();

        running_queue.push(proximo_processo);
        ready_queue.pop();

        set_running_queue(running_queue);
        set_ready_queue(ready_queue);


        cpu.run_process(proximo_processo, cpu); // Executa o próximo processo na CPU
        
        // Atualize o tempo restante do processo atual
        fila_de_executando.front().setRemainingTime(proximo_processo.getRemainingTime());
        
        if (proximo_processo.getRemainingTime() == 0) {
            finish_process(proximo_processo); // Se o processo terminou, finaliza ele
        }
        return !is_ready_queue_empty(); // Retorna se a fila de prontos está vazia, para saber se o escalonador terminou
    }
    
    // Parte da preempção
    if (!is_ready_queue_empty()) {
        Process& proximo_processo = fila_de_prontos.front();
        int prioridade_processo_atual = fila_de_executando.front().getPriority();
        int prioridade_proximo_processo = proximo_processo.getPriority();
        if (prioridade_proximo_processo > prioridade_processo_atual) {
        }

        auto [remaining_time, quantum_time] = cpu.run_process(fila_de_executando.front(), cpu);

        fila_de_executando.front().setRemainingTime(remaining_time);
        fila_de_executando.front().setCurrentQuantum(quantum_time);
        
        if (remaining_time == 0) {
            finish_process(fila_de_executando.front());
        }
        return !is_ready_queue_empty();
    } else {
        // Se não houver preempção, execute apenas o processo atual
        auto [remaining_time, quantum_time] = cpu.run_process(fila_de_executando.front(), cpu);

        fila_de_executando.front().setRemainingTime(remaining_time);
        fila_de_executando.front().setCurrentQuantum(quantum_time);
        
        if (remaining_time == 0) {
            finish_process(fila_de_executando.front());
        }
    }
    
    return false;
}
    bool check_preemption(Process& processo_atual) { return false; } // Sem preempção

};


