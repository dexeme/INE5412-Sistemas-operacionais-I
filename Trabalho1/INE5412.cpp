#include <iostream>
#include <fstream>
#include <string>

#include "file.h"
#include "process.h"
#include "scheduler.h"
#include "FCFSScheduler.cpp"
#include "SJFScheduler.cpp"
#include "INE5412.h"

using namespace std;

INE5412::INE5412() {}

INE5412::~INE5412() {}

void INE5412::start(string algorithm) {
    File file;
    vector<ProcessParams*> lista_de_processos = file.read_file();
    file.print_processes_params();
    Scheduler* scheduler = nullptr;
        if (algorithm == "FCFS") {
            cout << "FCFS" << endl;
            scheduler = new FCFSScheduler();
            }
        
        else if (algorithm == "SJF") {
            cout << "SJF" << endl;
            scheduler = new SJFScheduler();
            }
        
        if (scheduler) {
            cout << "Escalonador criado!" << endl;

            vector<ProcessParams> lista_de_processos_prontos;

            for (const ProcessParams* ptr : lista_de_processos) {
                lista_de_processos_prontos.push_back(*ptr);
            }

            scheduler->setListaDeProcessos(lista_de_processos_prontos);
            
            scheduler->start_scheduler();

            delete scheduler;

        } else {
            cout << "Algoritmo de escalonamento não reconhecido." << endl;
    }
}

