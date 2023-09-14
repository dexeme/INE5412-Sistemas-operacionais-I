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

int main(int argc, char** argv)
{
    // make [ entrada ] [ scheduler ]

    if (argc < 1) {
        std::cout << "Usage: ./scheduler <input_file> scheduler_type (optional)" << std::endl;
        return 1;
    }

    unsigned int scheduler_type = 0;

    if (argc == 2) { scheduler_type = atoi(argv[1]); } // Se o tipo de escalonador foi passado como parâmetro

    Kernel kernel;
    kernel.start(scheduler_type); // Inicia o sistema

    return 0;
}