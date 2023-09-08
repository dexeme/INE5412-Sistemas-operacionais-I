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
        Process processo_atual = get_current_process(); // Copia o processo atual em uma variável local
        queue<Process> fila_de_prontos = get_ready_queue(); // Copia a fila de prontos em uma variável local

        if (processo_atual.is_finished()) {
            cout << "DEBUG: Processo " << processo_atual.getPid() << " finalizado!" << endl;
            cout << "DEBUG: Tempo de retorno do processo " << processo_atual.getPid() << ": " << processo_atual.getRunningTime() << endl;

            // Remove o processo finalizado da fila de prontos
            set_ready_queue(fila_de_prontos);

            if (!is_ready_queue_empty()) {
                cout << "DEBUG: Processo na frente da fila de prontos: " << get_ready_queue().front().getPid() << endl;
                set_current_process(get_next_process()); // Pega o próximo processo da fila de prontos
                get_current_process().setState(RUNNING);
                run_process(get_current_process(), get_cpu());
            }

            return !get_ready_queue().empty(); // Retorna true se ainda há processos na fila de prontos
        }

        if (get_ready_queue().empty()) {
            cout << "DEBUG: Fila de prontos vazia!" << endl;
            return false;
        }

        // Atualiza o tempo restante do processo atual
        processo_atual.setRemainingTime(processo_atual.getRemainingTime() - 1);

        if (processo_atual.getRemainingTime() <= 0) {
            // Processo atual terminou seu tempo de CPU
            processo_atual.setState(FINISHED);
            cout << "DEBUG: Processo " << processo_atual.getPid() << " finalizado!" << endl;
            cout << "DEBUG: Tempo de retorno do processo " << processo_atual.getPid() << ": " << processo_atual.getRunningTime() << endl;

            // Remove o processo finalizado da fila de prontos
            get_ready_queue().pop();

            if (!get_ready_queue().empty()) {
                set_current_process(get_next_process()); // Pega o próximo processo da fila de prontos
                get_current_process().setState(RUNNING);
                run_process(get_current_process(), get_cpu());
            }
        } else {
            processo_atual.setRemainingTime(max(0, processo_atual.getRemainingTime()));
        }

        if (processo_atual.getState() == READY && check_preemption(processo_atual)) {
            // Processo atual é preemptado
            processo_atual.setState(READY);
            processo_atual.setDuration(processo_atual.getRemainingTime());
            add_process(processo_atual);

            Process processo_novo = get_ready_queue().front();
            set_current_process(processo_novo);
            get_ready_queue().pop();
            processo_novo.setState(RUNNING);
            run_process(processo_novo, get_cpu());
        }

        return true;
}


    vector<Process> organize_ready_queue(queue<Process> new_queue) {
        vector<Process> organized_queue;
        while (!new_queue.empty()) {
            organized_queue.push_back(new_queue.front());
            new_queue.pop();
        }
        sort(organized_queue.begin(), organized_queue.end(), [](Process a, Process b) {
            return a.getDuration() < b.getDuration();
        });
        cout << "DEBUG: ready queue size: " << get_ready_queue().size() << endl;
        cout << "DEBUG: Processo na frente da fila de prontos: " << get_ready_queue().front().getPid() << endl;
        cout << "DEBUG: new queue size: " << new_queue.size() << endl;
        return organized_queue;
    }

    bool check_preemption(Process processo_atual) {
        if (is_ready_queue_empty()) {
            return false;
        }

        Process processo_na_frente = get_ready_queue().front();
        return processo_atual.getDuration() > processo_na_frente.getDuration();
    }
};

