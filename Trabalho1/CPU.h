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
    public:

        CPU() {}
        

        virtual void save_context(Process processo) = 0;
        virtual void restore_context(Process processo) = 0;
        virtual void switch_context(Process processo_atual, Process processo_novo) = 0;
        virtual ~CPU() {}
        
        void run_process(Process &processo, CPU &cpu){
            processo.setState(RUNNING);
            int remainingTime = processo.getRemainingTime();
            if (remainingTime > 0)
            {
            processo.setRemainingTime(remainingTime - 1);
            cout << "CPU: Processo " << processo.getPid() << " rodando! | TR: " << processo.getRemainingTime() << "/" << processo.getDuration() << endl;
            }
        }


};

#endif