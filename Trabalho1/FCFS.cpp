#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class FCFS : public Scheduler {
public:

    FCFS(CPU& _cpu) : Scheduler(_cpu) {}
    

    ~FCFS() {}

    bool execute() {
        printa_fila_de_prontos();
        Process* processo_atual = get_current_process();
        CPU &cpu = get_cpu();
        queue<Process>& fila_de_prontos = get_ready_queue();

        if (processo_atual == nullptr) { // Se o processo atual é nulo
            if (is_ready_queue_empty()) { // Se a fila de prontos está vazia
                return false;
            }
            Process& proximo_processo = get_next_process();
            cpu.run_process(proximo_processo, cpu);
            if (proximo_processo.getRemainingTime() == 0) {
                finish_process(proximo_processo);
            }
            return !is_ready_queue_empty();
        }
        if (cpu.is_idle() && !processo_atual->is_finished()) { // Se a CPU está ociosa e o processo atual não está finalizado
            if (!fila_de_prontos.empty()) {
                Process processo_atual = fila_de_prontos.front();
                fila_de_prontos.pop();
                cpu.run_process(processo_atual, cpu);
            }
        }
        return false;
    }

    bool check_preemption(Process processo_atual) {
        // FCFS não tem preempção
        return false;
    }

    void organize_ready_queue(queue<Process> new_queue) {
        // não precisa organizar a fila de prontos
    }

    void printa_fila_de_prontos() {
        cout << "DEBUG: Fila de prontos: ";
        queue<Process> fila_de_prontos = get_ready_queue();
        while (!fila_de_prontos.empty()) {
            cout << fila_de_prontos.front().getPid() << " ";
            fila_de_prontos.pop();
        }
        cout << endl;
    }
};
