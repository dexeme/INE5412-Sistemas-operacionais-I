#ifndef INE5412_H
#define INE5412_H

#include <iostream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;

// Além disso, o programa de simulação deve abstrair o contexto de um processador (CPU) hipotético
// chamado INE5412 que possui 6 registradores de propósito geral, SP (stack pointer), PC (program
// counter) e ST (status), todos com 64 bits. Desta forma, cada abstração de processo também deve ter
// um contexto (como implementar o contexto de forma a permitir a mudança de processador para a
// abstração processo?). O programa de simulação deve então realizar a troca de contexto (salvar e
// restaurar o contexto do processo que estava em execução e do próximo processo a ser executado -
// Onde salvar o contexto do processo?



class INE5412 {
    private:
        int reg[6];
        int pc;
        int sp;
        int st;
    public:
        INE5412();
        ~INE5412();
        // void salvarContexto(ProcessParams processo);
        // void restaurarContexto(ProcessParams processo);
        void start(string scheduler);
};

#endif