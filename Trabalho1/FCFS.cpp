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
    printa_fila_de_prontos(); // DEBUG
    Process* processo_atual = get_current_process();
    CPU &cpu = get_cpu();
    queue<Process>& fila_de_prontos = get_ready_queue();
    queue<Process>& fila_de_executando = get_running_queue();

    if (!processo_atual) { // Se o processo atual é nulo
        if (fila_de_executando.empty()) {
            cout << "NULLPTR: Processo atual é nulo" << endl;
            if (fila_de_prontos.empty()) {
                return false;
            }
            cout << "DEBUG: Processo atual selecionado: " << fila_de_prontos.front().getPid() << endl;
            cout << "DEBUG: Fila de prontos não está vazia! Próximo processo: " << fila_de_prontos.front().getPid() << " | TR: " << fila_de_prontos.front().getRemainingTime() << "/" << fila_de_prontos.front().getDuration() << endl;
            int prioridade_atual = fila_de_executando.front().getPriority();

            Process& proximo_processo = get_next_process();
            fila_de_executando.push(proximo_processo);
            fila_de_prontos.pop();

            printa_fila_de_prontos();

            cpu.run_process(proximo_processo, cpu); // Executa o próximo processo na CPU

            // Atualize o tempo restante do processo atual
            fila_de_executando.front().setRemainingTime(proximo_processo.getRemainingTime());

            if (proximo_processo.getRemainingTime() == 0) {
                finish_process(proximo_processo); // Se o processo terminou, finaliza ele
            }
            return !fila_de_prontos.empty(); // Retorna se a fila de prontos está vazia, para saber se o escalonador terminou
        }

        // Parte da preempção
        if (!fila_de_prontos.empty()) {
            cout << "DEBUG: Checando se há processos de maior prioridade" << endl;
            Process& proximo_processo = fila_de_prontos.front();
            int prioridade_processo_atual = fila_de_executando.front().getPriority();
            int prioridade_proximo_processo = proximo_processo.getPriority();
            cout << "DEBUG: Prioridade do processo atual: " << prioridade_processo_atual << endl;
            cout << "DEBUG: Prioridade do próximo processo: " << prioridade_proximo_processo << endl;
            if (prioridade_proximo_processo > prioridade_processo_atual) {
                cout << "DEBUG: Processo atual é preemptado" << endl; // ISSO
            }
            int tempo_restante_do_processo_apos_execucao = cpu.run_process(fila_de_executando.front(), cpu);

            // Atualize o tempo restante do processo atual
            fila_de_executando.front().setRemainingTime(tempo_restante_do_processo_apos_execucao);

            if (tempo_restante_do_processo_apos_execucao == 0) {
                finish_process(fila_de_executando.front());
            }
            return !fila_de_prontos.empty();
        } else {
            // Se não houver preempção, execute apenas o processo atual
            int tempo_restante_do_processo_apos_execucao = cpu.run_process(fila_de_executando.front(), cpu);

            // Atualize o tempo restante do processo atual
            fila_de_executando.front().setRemainingTime(tempo_restante_do_processo_apos_execucao);

            if (tempo_restante_do_processo_apos_execucao == 0) {
                finish_process(fila_de_executando.front());
            }
        }

        return false;
    }

    // Restante do código para o caso em que há um processo em execução
}


    bool check_preemption(Process processo_atual) { return false; } // FCFS não tem preempção

    void organize_ready_queue(queue<Process> ready_queue) { } // FCFS não precisa organizar a fila de prontos

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
