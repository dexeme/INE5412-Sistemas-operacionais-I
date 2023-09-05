#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>

using namespace std;

class SJF : public Scheduler {
public:
    SJF(CPU& _cpu) : Scheduler(_cpu) {}

    ~SJF() {}

    void execute() {}
    // 2 4 3 1
void organize_ready_queue() {
    vector<Process> processos;
    
    cout << "Antes da organização: [";
    while (!is_ready_queue_empty()) {
        Process processo = get_next_process();
        processos.push_back(processo);
        cout << processo.getPid() << " (" << processo.getDuration() << ")";
        if (!is_ready_queue_empty()) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    sort(processos.begin(), processos.end(), [](Process& a, Process& b) {
        return a.getDuration() < b.getDuration();
    });

    cout << "Após a organização: [";
    for (size_t i = 0; i < processos.size(); i++) {
        cout << processos[i].getPid() << " (" << processos[i].getDuration() << ")";
        if (i != processos.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    // Adicione os processos organizados de volta à fila de prontos
    for (const Process& processo : processos) {
        add_process(processo);
    }

    cout << "Fila de prontos organizada com sucesso!" << endl;
}






};