#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <string>
#include <vector>

#include "process.h"
#include "INE5412.h"

using namespace std;

class Scheduler{

protected:

    vector<ProcessParams> listaDeProcessos;
    INE5412 cpu;
    int context_switch;

public:

    Scheduler() {}

    ~Scheduler() {}


    void setListaDeProcessos(vector<ProcessParams> listaDeProcessos) {
        this->listaDeProcessos = listaDeProcessos;

    }

    ProcessParams getNextProcess() {
    }

    void start_scheduler() {
        while (true) {
            ProcessParams processo = getNextProcess();
            if (processo.getPid() == -1) {
                break;
            }
            cout << "Executando processo " << processo.getPid() << endl;
        }
    }

    // Pega o próximo processo a ser executado
    
};

#endif