#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <unistd.h>
#include <algorithm>

#include "kernel.cpp"
#include "kernel.h"
#include "process_params.h"

using namespace std;

    int main() {
        Kernel kernel;
        kernel.start();
        File file;
        file.read_file();
        vector<ProcessParams> process_params = file.get_processes();

        bool running = true;
        int current_time = 0;
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - " << current_time << endl;
        while (running) {
            // Verifique se há processos para criar e enviar para o escalonador
            for (ProcessParams process : process_params) {
                if (process.get_creation_data() == current_time) {
                    Process new_process = kernel.create_process(process);
                    kernel.send_process(new_process); // Cria o processo e envia para o escalonador
                }
            }

            // Printa o current_time
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - " << current_time << endl;
            current_time++;

            
            sleep(1);

            // Verifique se o escalonador terminou de executar todos os processos
            kernel.scheduler->execute();
        }

        return 0;
    }