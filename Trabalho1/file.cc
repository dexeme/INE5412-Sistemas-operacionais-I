#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "file.h"
#include "process_params.h"

using namespace std;

File::File() {
    myfile.open("entrada.txt");
    if (!myfile.is_open()) {
        cout << "Erro ao abrir o arquivo!\n";
    }
}

File::~File() {
    for (unsigned int i = 0; i < processes.size(); i++) {
        ProcessParams p = processes[i];
    }
    if (myfile.is_open()) {
        cout << "Fechando arquivo!" << endl;
        myfile.close();
    }
}

vector<ProcessParams> File::read_file() {
    int a, b, c;
    if (!myfile.is_open()) {
        cout << "Arquivo não está aberto!" << endl;
        return processes;
    }
    while (myfile >> a >> b >> c) {
        ProcessParams *p = new ProcessParams(a, b, c);
        processes.push_back(*p);
    }
    cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
    return processes;
}

