#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "file.h"
#include "process.h"

using namespace std;

File::File() {
    myfile.open("entrada.txt");
    if (!myfile.is_open()) {
        cout << "Erro ao abrir o arquivo!\n";
    }
}

File::~File() {
    for (unsigned int i = 0; i < processes.size(); i++) {
        ProcessParams *p = processes[i];
        delete p;
    }
    if (myfile.is_open()) {
        cout << "Fechando arquivo!" << endl;
        myfile.close();
    }
}

void File::read_file() {
    int a, b, c;
    if (!myfile.is_open()) {
        cout << "Arquivo não está aberto!" << endl;
        return;
    }
    while (myfile >> a >> b >> c) {
        ProcessParams *p = new ProcessParams(a, b, c, size(processes));
        processes.push_back(p);
    }
    cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
}

void File::print_processes_params() {
    for (const auto& process : processes) {
        cout << "Process: CreationTime=" << process->getCreationTime()
             << " Duration=" << process->getDuration()
             << " Priority=" << process->getPriority()
             << " PID=" << process->getPid()
             << endl;
    }
}
