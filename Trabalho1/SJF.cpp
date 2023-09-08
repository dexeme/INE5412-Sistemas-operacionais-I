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
        Process* processo_atual = get_current_process();
        queue<Process>& fila_de_prontos = get_ready_queue();
        
        if (processo_atual == nullptr) {
            cout << "DEBUG: Processo atual é nulo" << endl;
            if (is_ready_queue_empty()) {
                cout << "DEBUG: Fila de prontos está vazia" << endl;
                return false;
            }
        }
        if (processo_atual != nullptr && !processo_atual->is_finished()) {
            cout << "DEBUG: Processo atual não é nulo e não está finalizado" << endl;
            if (check_preemption(*processo_atual)) {
                cout << "DEBUG: Processo atual é preemptado" << endl;
                switch_process(*processo_atual, get_next_process());
                return true;
            }
            if (processo_atual->getRemainingTime() == get_next_process().getRemainingTime()) {
                cout << "DEBUG: Processo atual e próximo processo tem o mesmo tempo restante" << endl;
                run_process(*processo_atual, get_cpu());
                return true;
            }
        }
        if (!is_ready_queue_empty() && processo_atual != nullptr && processo_atual->getState() == RUNNING) {
            cout << "DEBUG: Processo atual não é nulo e está rodando" << endl;
            run_process(*processo_atual, get_cpu());
            if (processo_atual->getRemainingTime() == 0) {
                cout << "DEBUG: Processo atual terminou" << endl;
                finish_process(*processo_atual);
                return !is_ready_queue_empty();
            }
        }

        return true;
    }

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

    bool check_preemption(Process& processo_atual) {
        if (is_ready_queue_empty()) {
            return false;
        }

        Process& processo_na_frente = get_ready_queue().front();
        return processo_atual.getDuration() > processo_na_frente.getDuration();
    }

    void finish_process(Process& processo) {
        processo.setState(FINISHED);
        set_current_process(nullptr);
        cout << "DEBUG: Processo " << processo.getPid() << " finalizado!" << endl;
        // Tira o processo da fila de prontos
        queue<Process> fila_de_prontos = get_ready_queue();
        fila_de_prontos.pop();
        set_ready_queue(fila_de_prontos);
    }
};


