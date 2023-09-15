#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;

// Além disso, o programa de simulação deve abstrair o contexto de um processador (CPU) hipotético
// chamado CPU que possui 6 registradores de propósito geral, SP (stack pointer), PC (program
// counter) e ST (status), todos com 64 bits. Desta forma, cada abstração de processo também deve ter
// um contexto (como implementar o contexto de forma a permitir a mudança de processador para a
// abstração processo?). O programa de simulação deve então realizar a troca de contexto (salvar e
// restaurar o contexto do processo que estava em execução e do próximo processo a ser executado -
// Onde salvar o contexto do processo?



class CPU {
    private:
        
        bool idle = true;

    public:

        CPU() {}
        
        bool is_idle() { return idle; }

        
        virtual ~CPU() {}
        
        tuple<int, int> run_process(Process &processo, CPU &cpu){

            idle = false;

            processo.setState(RUNNING);
            processo.setRunningTime(processo.getRunningTime() + 1);
            processo.setCurrentQuantum(processo.getCurrentQuantum() + 1);

            int quantumTime = processo.getCurrentQuantum();

            if (processo.getRemainingTime() > 0)
            {
            processo.setRemainingTime(processo.getRemainingTime() - 1);
            }
            else
            {
            }

            int remainingTime = processo.getRemainingTime();

            idle = true;

            return {remainingTime, quantumTime};
        }


};

#endif