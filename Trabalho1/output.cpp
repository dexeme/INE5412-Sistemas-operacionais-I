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
};
