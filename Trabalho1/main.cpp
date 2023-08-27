#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ProcessParams {
public:
    ProcessParams(int a, int b, int c) : paramA(a), paramB(b), paramC(c) {}

    friend ostream& operator<<(ostream& os, const ProcessParams& p) {
        os << "Param A: " << p.paramA << ", Param B: " << p.paramB << ", Param C: " << p.paramC << endl;
        return os;
    }

private:
    int paramA;
    int paramB;
    int paramC;
};

class File {
public:
    File() {
        myfile.open("entrada/entrada.txt");
        if (!myfile.is_open()) {
            cout << "Erro ao abrir o arquivo!\n";
        }
    }

    ~File() {
        for (unsigned int i = 0; i < processes.size(); i++) {
            ProcessParams *p = processes[i];
            delete p;
        }
        if (myfile.is_open()) {
			cout << "Fechando arquivo!" << endl;
            myfile.close();
        }
    }

    void read_file() {
        int a, b, c;
        if (!myfile.is_open()) {
            cout << "Arquivo não está aberto!" << endl;
            return;
        }
        while (myfile >> a >> b >> c) {
            ProcessParams *p = new ProcessParams(a, b, c);
            processes.push_back(p);
        }
        cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
    }

    void print_processes_params() {
        for (vector<ProcessParams *>::iterator iter = processes.begin(); iter < processes.end(); iter++) {
            ProcessParams *p = *iter;
            cout << *p;
        }
    }

private:
    ifstream myfile;
    vector<ProcessParams *> processes;
};

int main() {
    File f;
    f.read_file();
    f.print_processes_params();
    return 0;
}
