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

        cout << "DEBUG: Processo atual: " << processo_atual.getPid() << endl;
        cout << "DEBUG: Processo atual tem duração: " << processo_atual.getDuration() << endl;
        cout << "DEBUG: Processo atual tem tempo restante: " << processo_atual.getRemainingTime() << endl;

        if (fila_de_prontos.empty()) {
            cout << "DEBUG: Fila de prontos vazia!" << endl;
            return false;
        }

        // Se o processo atual não foi finalizado, verifica se há processos na fila de prontos
        // Se houver, verifica se o processo atual tem duração maior que o processo na frente da fila de prontos
        // Se tiver, interrompe o processo atual e coloca na fila de prontos
        if (processo_atual.getRemainingTime() > get_next_process().getRemainingTime()) {
            cout << "DEBUG: Processo " << processo_atual.getPid() << " interrompido!" << endl;
            processo_atual.setState(READY);
            fila_de_prontos.push(processo_atual);
            set_ready_queue(fila_de_prontos);
            return true;
        }

        // Se o processo atual foi finalizado, verifica se há processos na fila de prontos
        if (processo_atual.is_finished()) {
            cout << "DEBUG: Processo " << processo_atual.getPid() << " finalizado!" << endl;

            fila_de_prontos.pop(); // Remove o processo finalizado da fila de prontos
            
            set_ready_queue(fila_de_prontos); // Atualiza a fila de prontos
            return !is_ready_queue_empty(); // Retorna true se ainda há processos na fila de prontos
            }

            // Se o processo atual não foi finalizado e não foi interrompido, executa o processo
            // e decrementa o tempo restante do processo
            if (!is_ready_queue_empty() && processo_atual.getState() == RUNNING) {
                processo_atual.setRemainingTime(processo_atual.getRemainingTime() - 1);
                cout << "DEBUG: Processo " << processo_atual.getPid() << " executando!" << endl;
            }
            
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

