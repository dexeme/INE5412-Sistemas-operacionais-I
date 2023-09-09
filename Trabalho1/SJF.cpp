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
        CPU &cpu = get_cpu();
        queue<Process>& fila_de_prontos = get_ready_queue();
        
        if (processo_atual == nullptr || processo_atual->is_finished()) {
            cout << "NULLPTR: Processo atual é nulo" << endl;
            if (is_ready_queue_empty()) {
                cout << "READY-QUEUE: Fila de processos vazia!" << endl;
                return false;
            }
            Process& proximo_processo = get_next_process();
            cout << "DEBUG: Fila de prontos não está vazia! Próximo processo: " << proximo_processo.getPid() << " | TR: " << proximo_processo.getRemainingTime() << "/" << proximo_processo.getDuration() << endl;

            if (check_preemption(proximo_processo)) {
                cout << "\nDEBUG: Processo atual é preemptado" << endl;
                cout << "DEBUG: Processo atual: " << processo_atual->getPid() << endl;
                cout << "DEBUG: Próximo processo: " << proximo_processo.getPid() << "\n" << endl;
                switch_process(*processo_atual, proximo_processo);
                return true;
            }

            cpu.run_process(proximo_processo, cpu);
            if (proximo_processo.getRemainingTime() == 0) {
                cout << "DEBUG: Processo atual terminou" << endl;
                finish_process(proximo_processo);
            }
            return !is_ready_queue_empty();
        }

        cout << "\nDEBUG: Processo atual não é nulo e não está finalizado" << endl;
        cout << "DEBUG: Processo atual: " << processo_atual->getPid() << endl;
        cout << "DEBUG: Tempo restante: " << processo_atual->getRemainingTime() << "\n" << endl;

        if (check_preemption(*processo_atual)) {
            cout << "\nDEBUG: Processo atual é preemptado" << endl;
            cout << "DEBUG: Processo atual: " << processo_atual->getPid() << endl;
            cout << "DEBUG: Próximo processo: " << get_next_process().getPid() << "\n" << endl;

            switch_process(*processo_atual, get_next_process());
            return true;
        }

        cpu.run_process(*processo_atual, cpu);
        if (processo_atual->getRemainingTime() == 0) {
            cout << "DEBUG: Processo atual terminou" << endl;
            finish_process(*processo_atual);
            return !is_ready_queue_empty();
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
        cout << "DEBUG: Processo " << processo.getPid() << " finalizado!" << endl;
        // Tira o processo da fila de prontos
        queue<Process> fila_de_prontos = get_ready_queue();
        fila_de_prontos.pop();
        set_ready_queue(fila_de_prontos);
    }
};


