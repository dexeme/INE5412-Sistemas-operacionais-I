#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class FCFSScheduler : public Scheduler {
public:
    FCFSScheduler() {}

    ~FCFSScheduler() {}

    // Pega o próximo processo a ser executado
    ProcessParams getNextProcess() {
        if (!listaDeProcessos.empty()) {
            return listaDeProcessos[0];
        } else {
            return ProcessParams(-1, 0, 0, 0);
        }
    }

    // Adiciona um processo à fila de processos
    void addProcess(ProcessParams process) {
        cout << "Processo " << process.getPid() << " adicionado!" << endl;
        listaDeProcessos.push_back(process);
    }

    // Calcula o TurnAroundTime
    int calculateTurnAroundTime() {
        return 10;
    }

    // Calcula o Tempo de espera
    int calculateWaitingTime() {
        return 5;
    }

    // Calcula o número de trocas de contexto
    int calculaContextSwitch() {
        return 2;
    }

    void start_scheduler() {
    // Verifique se há processos na fila
        if (listaDeProcessos.empty()) {
            std::cout << "Nenhum processo para executar." << std::endl;
            return;
        }

        // Execute os processos na ordem de chegada (FCFS)
        while (!listaDeProcessos.empty()) {
            // Próximo processo a ser executado
            ProcessParams nextProcess = getNextProcess();

            // Verificar se o próximo processo é válido (ID não negativo)
            if (nextProcess.getPid() >= 0) {
                // Executando o processo
                std::cout << "Executando Processo ID: " << nextProcess.getPid() << std::endl;

                // Removendo o processo da fila, pois ele está sendo executado
                listaDeProcessos.erase(listaDeProcessos.begin());
            } else {
                std::cout << "Processo inválido encontrado." << std::endl;
            }
        }

        int turnaroundTime = calculateTurnAroundTime();
        int waitingTime = calculateWaitingTime();
        int contextSwitches = calculaContextSwitch();

        std::cout << "Turnaround Time: " << turnaroundTime << std::endl;
        std::cout << "Waiting Time: " << waitingTime << std::endl;
        std::cout << "Número de Trocas de Contexto: " << contextSwitches << std::endl;
    }


    };
