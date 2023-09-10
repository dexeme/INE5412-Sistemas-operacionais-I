#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class PRIO : public Scheduler {
public:
    PRIO(CPU& _cpu) : Scheduler(_cpu) {}

    ~PRIO() {}

    bool execute() {}

    bool check_preemption(Process processo_atual) { return false; } // Sem preempção

    void organize_ready_queue(queue<Process> new_queue) {}
};
