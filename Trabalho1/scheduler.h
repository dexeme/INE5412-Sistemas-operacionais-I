#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;

class Scheduler{
    Escalonador();

    virtual ~Escalonador();

    virtual vector<ProcessParams> processes; // Fila de processos

    virtual ProcessParams getNextProcess() = 0; // Pega próximo processo a ser executado

    virtual void addProcess(ProcessParams process) = 0; // Adiciona processo na fila de processos
    
    virtual int calculateTurnAroundTime() = 0; // Calcula o tempo de retorno médio dos processos

    virtual int calculateWaitingTime() = 0; // Calcula o tempo de espera médio dos processos

    virtual int calculaContextSwitch() = 0; // Calcula o número de trocas de contexto
    
}