#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class PRIO : public Scheduler {
public:
    PRIO(CPU& _cpu) : Scheduler(_cpu) {}

    ~PRIO() {}

    // 4 2 1 3
    bool execute() {
        printa_fila_de_prontos(); // DEBUG
        Process* processo_atual = get_current_process();
        CPU &cpu = get_cpu();
        queue<Process>& fila_de_prontos = get_ready_queue();

        if (processo_atual == nullptr) { // Se o processo atual é nulo
            if (is_ready_queue_empty()) {
                return false;
            }
            Process& proximo_processo = get_next_process();
            cpu.run_process(proximo_processo, cpu); // Executa o próximo processo na CPU
            if (proximo_processo.getRemainingTime() == 0) {
                finish_process(proximo_processo); // Se o processo terminou, finaliza ele
            }
            return !is_ready_queue_empty(); // Retorna se a fila de prontos está vazia, para saber se o escalonador terminou
        }
        if (cpu.is_idle() && !processo_atual->is_finished()) { // Se a CPU está livre e o processo atual não está finalizado
            if (!fila_de_prontos.empty()) {
                Process processo_atual = fila_de_prontos.front();
                fila_de_prontos.pop();
                cpu.run_process(processo_atual, cpu);
            }
        }
        return false;
    }

    bool check_preemption(Process processo_atual) { return false; } // Sem preempção

    void organize_ready_queue(queue<Process> ready_queue) {
        vector<Process> processos;
        while (!ready_queue.empty()) {
            processos.push_back(ready_queue.front());
            ready_queue.pop();
        }
        sort(processos.begin(), processos.end(), [](Process& a, Process& b) {
            return a.getDuration() < b.getDuration();
        });
        for (Process processo : processos) {
            ready_queue.push(processo);
        }
        set_ready_queue(ready_queue);
    }
};
