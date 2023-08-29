#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>

using namespace std;

class SJFScheduler : public Scheduler {
public:
    SJFScheduler() {}

    ~SJFScheduler() {}

    // Pega próximo processo a ser executado
    ProcessParams getNextProcess() {
        if (!listaDeProcessos.empty()) {
            ProcessParams shortestJob = listaDeProcessos[0];

            for (ProcessParams& process : listaDeProcessos) {
                if (process.getDuration() < shortestJob.getDuration()) {
                    shortestJob = process;
                }
            }

            // Remove o processo da lista de processos
            
            return shortestJob;
        } else {
            // Se não houver processos na lista, retorne um objeto ProcessParams vazio
            return ProcessParams(-1, 0, 0, 0);
        }
    }


    // Salva contexto do processo
    void saveContext(ProcessParams updatedProcess) {
        for (ProcessParams& process : listaDeProcessos) {
            if (process.getPid() == updatedProcess.getPid()) {
                cout << "Processo " << process.getPid() << " atualizado!" << endl;
                process = updatedProcess;
                break;
            }
        }
    }

    // Adiciona processo na fila de processos
    void addProcess(ProcessParams process) {
        int menor_duracao = process.getDuration();
        for (ProcessParams& process : listaDeProcessos) {
            if (process.getDuration() < menor_duracao) {
                menor_duracao = process.getDuration();
            }

        cout << "Processo " << process.getPid() << " adicionado!" << endl;
        listaDeProcessos.push_back(process);
    }
}

    // Calcula o TurnAroundTime
    int calculateTurnAroundTime() {
        return 1;
    }

    // Calcula o Tempo de espera
    int calculateWaitingTime() {
        return 1;
    }

    // Calcula o número de trocas de contexto
    int calculaContextSwitch() {
        return 1;
    }

    // Inicia o escalonador

    void start_scheduler() {
        // Verifique se há processos na fila
        if (listaDeProcessos.empty()) {
            std::cout << "Nenhum processo para executar." << std::endl;
            return;
        }

        // Ordem os processos por tempo de execução (menor primeiro)
        sort(listaDeProcessos.begin(), listaDeProcessos.end(), [](const ProcessParams& a, const ProcessParams& b) {
            return a.getDuration() < b.getDuration();
        });

        // Execute os processos em ordem
        for (const ProcessParams& process : listaDeProcessos) {
            std::cout << "Executando Processo ID: " << process.getPid() << std::endl;

           //

        }
    }
    };