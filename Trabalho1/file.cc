#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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
    for (unsigned int i = 0; i < processes_params.size(); i++) {
        ProcessParams p = processes_params[i];
    }
    if (myfile.is_open()) {
        cout << "Fechando arquivo!" << endl;
        myfile.close();
    }
}

void File::read_file() {
    int a, b, c, d;
    if (!myfile.is_open()) {
        cout << "Arquivo não está aberto!" << endl;
        return;
    }
    while (myfile >> a >> b >> c) {
        cout << "DEBUG: Processo " << size(processes_params)+1 << " lido do arquivo" << endl;
        ProcessParams p = ProcessParams(a, b, c, size(processes_params)+1);
        processes_params.push_back(p);
    }
    cout << "Quantidade de processos lidos do arquivo: " << processes_params.size() << endl;
    sort(processes_params.begin(), processes_params.end(), [](ProcessParams a, ProcessParams b) {
            return a.get_creation_data() < b.get_creation_data();});
}