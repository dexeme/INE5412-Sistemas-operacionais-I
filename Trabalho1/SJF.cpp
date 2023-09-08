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
        printa_fila_de_prontos();
        // Se não há processo em execução, pega o primeiro da fila de prontos
        Process* processo_atual = get_current_process();
        queue<Process>& fila_de_prontos = get_ready_queue();
        if (get_current_process() == nullptr) {
            if (is_ready_queue_empty()) {
                printa_fila_de_prontos();
                return true;
            }
        }
        if (processo_atual != nullptr && !processo_atual->is_finished()) {
            if (check_preemption(*processo_atual)) {
                switch_process(*processo_atual, get_next_process());
                return true;
            }
            if (processo_atual->getRemainingTime() == get_next_process().getRemainingTime()) {
                run_process(*processo_atual, get_cpu());
                return true;
            }
        }
        if (!is_ready_queue_empty() && processo_atual != nullptr && processo_atual->getState() == RUNNING) {
            run_process(*processo_atual, get_cpu());
            if (processo_atual->is_finished()) {
                finish_process(*processo_atual);
                return !is_ready_queue_empty();
            }
        }

        return true;
    }

    vector<Process> organize_ready_queue(queue<Process> new_queue) {
        vector<Process> organized_queue;
        while (!new_queue.empty()) {
            organized_queue.push_back(new_queue.front());
            new_queue.pop();
        }
        sort(organized_queue.begin(), organized_queue.end(), [](Process& a, Process& b) {
            return a.getDuration() < b.getDuration();
        });

        cout << "DEBUG: Processo na frente da fila de prontos: " << get_ready_queue().front().getPid() << endl;
        printa_fila_de_prontos();
        return organized_queue;
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


