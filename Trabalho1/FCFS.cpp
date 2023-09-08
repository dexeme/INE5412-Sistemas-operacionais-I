#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class FCFS : public Scheduler {
public:
    FCFS(CPU& _cpu) : Scheduler(_cpu) {}

    ~FCFS() {}

    bool execute() {return true;}

    bool check_preemption(Process processo_atual) {return false;}

    void virtual organize_ready_queue(queue<Process> new_queue) {
        // não precisa organizar a fila de prontos
    }
};
