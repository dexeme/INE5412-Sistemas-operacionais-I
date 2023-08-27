#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "..headers/file.h"
#include "..headers/process.h"

using namespace std;

File::File() {
    myfile.open("entrada.txt");
    if (!myfile.is_open()) {
        cout << "Erro ao abrir o arquivo!\n";
    }
}

File::~File() {
    for (int i = 0; i < processes.size(); i++) {
        ProcessParams *p = processes[i];
        delete p;
    }
    // Close the file in the destructor
    if (myfile.is_open()) {
        myfile.close();
    }
}

void File::read_file() { // Remove the 'string file_name' parameter
    int a, b, c;
    if (!myfile.is_open()) {
        cout << "Arquivo não está aberto!" << endl;
        return; // Return early if the file is not open
    }
    while (myfile >> a >> b >> c) {
        ProcessParams *p = new ProcessParams(a, b, c);
        processes.push_back(p);
    }
    cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
}

void File::print_processes_params() { // Add File:: scope specifier
    for (vector<ProcessParams *>::iterator iter = processes.begin(); iter < processes.end(); iter++) {
        ProcessParams *p = *iter;
        cout << *p;
    }
}
