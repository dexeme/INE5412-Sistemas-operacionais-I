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
#include "output.cpp"

using namespace std;

int main()
{
    Kernel kernel;
    kernel.start(); // Inicia o sistema

    File file;
    file.read_file(); // Lê o arquivo de entrada

    Output output; // Classe responsável por imprimir os dados de saída

    vector<ProcessParams> process_params = file.get_processes(); // Pega os parâmetros dos processos do arquivo

    bool running = true;
    int current_time = 0; // Tempo atual do sistema
    
    output.print_header(); // Imprime "tempo      P1  P2  P3  P4"

    while (running) // Enquanto o escalonador não terminar de executar todos os processos
    {
        for (ProcessParams process : process_params)
        {
            if (process.get_creation_data() == current_time) // Se o processo deve ser criado nesse tempo
            {
                Process new_process = kernel.create_process(process); // Cria o processo
                kernel.send_process(new_process); // Envia o processo para o escalonador
            }
        }

        current_time++;

        //queue<Process> running_queue = kernel.scheduler->get_running_queue();

        //queue<Process> ready_queue = kernel.scheduler->get_ready_queue();

        //output.print_line(current_time, running_queue, ready_queue);

        sleep(1); // Espera 1 segundo

        kernel.scheduler->execute(); // Executa o escalonador
    }

    return 0;
}