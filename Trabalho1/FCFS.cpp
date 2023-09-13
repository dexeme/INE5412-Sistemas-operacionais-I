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

    Process* processo_atual = get_current_process();
    CPU &cpu = get_cpu();
    queue<Process>& fila_de_prontos = get_ready_queue();
    queue<Process>& fila_de_executando = get_running_queue();

    if (!processo_atual) { // Se o processo atual é nulo
        if (fila_de_executando.empty()) {
            if (fila_de_prontos.empty()) {
                return false;
            }

            Process& proximo_processo = get_next_process();
            fila_de_executando.push(proximo_processo);
            fila_de_prontos.pop();


            cpu.run_process(proximo_processo, cpu); // Executa o próximo processo na CPU

            // Atualize o tempo restante do processo atual
            fila_de_executando.front().setRemainingTime(proximo_processo.getRemainingTime());

            if (proximo_processo.getRemainingTime() == 0) {
                finish_process(proximo_processo); // Se o processo terminou, finaliza ele
            }
            return !fila_de_prontos.empty(); // Retorna se a fila de prontos está vazia, para saber se o escalonador terminou
        }
            auto [remaining_time, quantum_time] = cpu.run_process(fila_de_executando.front(), cpu); // Executa o próximo processo na CPU

            // Atualize o tempo restante do processo atual
            fila_de_executando.front().setRemainingTime(remaining_time);
            fila_de_executando.front().setCurrentQuantum(quantum_time);

            if (remaining_time == 0) {
                finish_process(fila_de_executando.front());
            }
            return !fila_de_prontos.empty();
    } else {
            // Se não houver preempção, execute apenas o processo atual
            cpu.run_process(fila_de_executando.front(), cpu);

            if (fila_de_executando.front().getRemainingTime() == 0) {
                finish_process(fila_de_executando.front());
            }
        }

        return false;
    }

    // Restante do código para o caso em que há um processo em execução



    bool check_preemption(Process processo_atual) { return false; } // FCFS não tem preempção

};
