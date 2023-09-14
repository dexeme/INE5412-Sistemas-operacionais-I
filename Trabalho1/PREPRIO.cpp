#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class PREPRIO : public Scheduler {
public:
    PREPRIO(CPU& _cpu) : Scheduler(_cpu) {}

    ~PREPRIO() {}

bool execute() {
    clear_finished_queue();
    CPU &cpu = get_cpu();
    queue<Process> &fila_de_prontos = get_ready_queue();
    queue<Process> &fila_de_executando = get_running_queue();

    if (is_ready_queue_empty()) {
        if (is_running_queue_empty()) {
            return false;
        }
    }

    if (!is_running_queue_empty()) {
        Process &processo_atual = fila_de_executando.front();
        if (!is_ready_queue_empty()) {
            Process &proximo_processo = fila_de_prontos.front();
            if (proximo_processo.getPriority() < processo_atual.getPriority()) {
                // Preempção: O próximo processo tem prioridade mais alta
                switch_process(processo_atual, proximo_processo);
                fila_de_prontos.push(processo_atual);
                fila_de_executando.pop();
                fila_de_executando.push(proximo_processo);
                fila_de_prontos.pop();
                auto [remaining_time, quantum_time] = cpu.run_process(fila_de_executando.front(), cpu);
                fila_de_executando.front().setRemainingTime(remaining_time);
                fila_de_executando.front().setCurrentQuantum(quantum_time);
                if (remaining_time == 0) {
                    finish_process(fila_de_executando.front());
                }
                return true; // Houve preempção, continue com o próximo processo
            }
        }
        // Não houve preempção, execute apenas o processo atual
        auto [remaining_time, quantum_time] = cpu.run_process(processo_atual, cpu);
        processo_atual.setRemainingTime(remaining_time);
        processo_atual.setCurrentQuantum(quantum_time);
        if (remaining_time == 0) {
            finish_process(processo_atual);
        }
    } else {
        // Se não há processo em execução, inicie um novo
        Process &proximo_processo = get_next_process();
        fila_de_executando.push(proximo_processo);
        fila_de_prontos.pop();
        auto [remaining_time, quantum_time] = cpu.run_process(fila_de_executando.front(), cpu);
        fila_de_executando.front().setRemainingTime(remaining_time);
        fila_de_executando.front().setCurrentQuantum(quantum_time);
        if (remaining_time == 0) {
            finish_process(fila_de_executando.front());
        }
    }

    return true; // Continuar a execução do escalonador
}



    bool check_preemption(Process processo_atual) {} // TODO: Implementar preempção

};
