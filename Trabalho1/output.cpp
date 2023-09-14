#include <iostream>
#include <iomanip>
#include "process.h"

using namespace std;

class Output {
private:
    int waitingTimes[4] = {0}; // Um contador local para o tempo de espera de cada processo

public:
    void print_header() {
        cout << "tempo         P1  P2  P3  P4" << endl;
    }

    string getStatus(int pid, queue<Process> processos_prontos, queue<Process> processos_em_execucao, queue<Process> processos_finalizados) {
        queue<Process> temp_prontos = processos_prontos;
        queue<Process> temp_execucao = processos_em_execucao;
        queue<Process> temp_finalizados = processos_finalizados;

        while (!temp_prontos.empty()) {
            if (temp_prontos.front().getPid() == pid) {
                return "--";
            }
            temp_prontos.pop();
        }

        while (!temp_execucao.empty()) {
            if (temp_execucao.front().getPid() == pid) {
                return "##";
            }
            temp_execucao.pop();
        }

        while (!temp_finalizados.empty()) {
            if (temp_finalizados.front().getPid() == pid) {
                return "##";
            }
            temp_finalizados.pop();
        }

        return "  ";
    }

    void print_line(int current_time, queue<Process> processos_em_execucao, queue<Process> processos_prontos, queue<Process> processos_finalizados) {
        cout << setw(3) << left << current_time << "- " << setw(2) << right << current_time + 1 << "       ";
        for (int i = 1; i <= 4; i++) {
            string status = getStatus(i, processos_prontos, processos_em_execucao, processos_finalizados);
            cout << status;
            
            // Verifica se o processo está no estado "READY" e incrementa o tempo de espera localmente
            if (status == "--") {
                waitingTimes[i - 1]++;
            }
            
            if (i < 4) {
                cout << "  ";
            }
        }
        cout << endl;
    }

    void print_process_information(queue<Process> ready_to_print_info) {
        int total_turnaround_time = 0;
        int total_process = 0;
        cout << "Processo  Turnaround time          Waiting time" << endl;
        while (!ready_to_print_info.empty()) {
            total_turnaround_time += ready_to_print_info.front().getFinishTime() + 1;
            total_process++;
            cout << setw(8) << left << ready_to_print_info.front().getPid() << setw(10) << right << ready_to_print_info.front().getFinishTime() + 1 << setw(24) << right << waitingTimes[ready_to_print_info.front().getPid() - 1] << endl;
            
            ready_to_print_info.pop();
        }
        cout << "Tempo médio de turnaround: " << total_turnaround_time / total_process << endl;


    }

    void print_total_context_changes(int total_context_changes) {
        cout << "Total de trocas de contexto: " << total_context_changes << endl;
    }
};