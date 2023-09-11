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
    printa_fila_de_prontos(); // DEBUG
    queue<Process>& fila_de_executando = get_running_queue();
    queue<Process>& fila_de_prontos = get_ready_queue();
    CPU &cpu = get_cpu();

    const int quantum = 2; // Define o quantum como 2 segundos

    if (!is_running_queue_empty()) {
        if (is_ready_queue_empty()) {
            cout << "DEBUG: Fila de prontos vazia, executando último processo" << endl;
        }

        Process& processo_atual = fila_de_executando.front();
        cout << "DEBUG: Processo atual selecionado: " << processo_atual.getPid() << endl;
        cout << "DEBUG: Fila de prontos não está vazia! Próximo processo: " << fila_de_prontos.front().getPid() << " | TR: " << fila_de_prontos.front().getRemainingTime() << "/" << fila_de_prontos.front().getDuration() << endl;

        int tempo_decorrido = cpu.run_process(processo_atual, cpu); // Executa o processo atual

        // Verifica se o processo atual ainda não terminou
        if (tempo_decorrido < quantum && !processo_atual.is_finished()) {
            int tempo_restante = processo_atual.getRemainingTime();
            if (tempo_restante <= quantum - tempo_decorrido) {
                // O processo terminará durante esse quantum
                processo_atual.setRemainingTime(0);
                finish_process(processo_atual);
                cout << "DEBUG: Processo atual terminou durante o quantum" << endl;
            } else {
                // O processo ainda tem tempo restante após o quantum
                processo_atual.setRemainingTime(tempo_restante - (quantum - tempo_decorrido));
                cout << "DEBUG: Processo atual executou por " << (quantum - tempo_decorrido) << " segundos." << endl;
            }
        }
        return !is_ready_queue_empty(); // Retorna se a fila de prontos está vazia, para saber se o escalonador terminou
    }

    // Parte da preempção
    if (!is_ready_queue_empty()) {
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
        return !is_ready_queue_empty();
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

    bool check_preemption(Process processo_atual) {} // TODO: Implementar preempção

    void organize_ready_queue(queue<Process> new_queue) {}
};
