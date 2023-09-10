#include <iostream>

#include "process.h"

using namespace std;

// Classe responsável por imprimir os dados de saída
class Output {
    public:
        void print_header(){
            cout << "tempo  P1  P2  P3  P4" << endl;
        }

    string getStatus(int pid, queue<Process> processos_prontos, queue<Process> processos_em_execucao) {
        for (int i = 0; i < processos_prontos.size(); i++) {
            if (processos_prontos.front().getPid() == pid) {
                return " -- ";
            }
            processos_prontos.push(processos_prontos.front());
            processos_prontos.pop();
        }
        for (int i = 0; i < processos_em_execucao.size(); i++) {
            if (processos_em_execucao.front().getPid() == pid) {
                return " ## ";
            }
            processos_em_execucao.push(processos_em_execucao.front());
            processos_em_execucao.pop();
        }
        return "    ";
    }

    void print_line(int current_time, queue<Process> processos_em_execucao, queue<Process> processos_prontos) {
        cout << current_time - 1 << "-" << current_time << "   ";
        for (int i = 1; i <= 4; i++) {
            cout << getStatus(i, processos_prontos, processos_em_execucao);
        }
        cout << endl;
    }

};