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
    kernel.start();
    File file;
    file.read_file();
    Output output;
    vector<ProcessParams> process_params = file.get_processes();

    bool running = true;
    int current_time = 0;
    
    output.print_header();

    while (running)
    {
        for (ProcessParams process : process_params)
        {
            if (process.get_creation_data() == current_time)
            {
                Process new_process = kernel.create_process(process);
                kernel.send_process(new_process); // Cria o processo e envia para o escalonador
            }
        }

        current_time++;

        queue<Process> running_queue = kernel.scheduler->get_running_queue();
        queue<Process> ready_queue = kernel.scheduler->get_ready_queue();
        output.print_line(current_time, running_queue, ready_queue);

        sleep(1);

        // Verifique se o escalonador terminou de executar todos os processos
        kernel.scheduler->execute();
    }

    return 0;
}