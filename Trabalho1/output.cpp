#include <iostream>
#include <iomanip>
#include "process.h"

using namespace std;

class Output {
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
            if (i < 4) {
                cout << "  ";
            }
        }
        cout << endl;
    }

    // Turnaround time (tempo transcorrido desde o momento em que o processo é criado até o
    // instante em que termina sua execução). Imprimir o turnaround time para cada processo e
    // também o valor médio.
    // • Tempo média de espera (soma dos períodos em que o processo estava no seu estado pronto).
    // • Número total de trocas de contexto (considerar que na primeira execução do primeiro
    // processo há uma troca de contexto).
    // • Diagrama de tempo de execução.

    void print_process_information(queue<Process> ready_to_print_info) {
        int total_turnaround_time = 0;
        int total_process = 0;
        cout << "Processo  Turnaround time" << endl;
        while (!ready_to_print_info.empty()) {
            total_turnaround_time += ready_to_print_info.front().getFinishTime() + 1;
            total_process++;
            cout << setw(8) << left << ready_to_print_info.front().getPid() << setw(10) << right << ready_to_print_info.front().getFinishTime() + 1 << setw(24) << right << endl;
            ready_to_print_info.pop();
        }
        cout << "Tempo médio de turnaround: " << total_turnaround_time / total_process << endl;

    }

    void print_total_context_changes(int total_context_changes) {
        cout << "Total de trocas de contexto: " << total_context_changes << endl;
    }
};
