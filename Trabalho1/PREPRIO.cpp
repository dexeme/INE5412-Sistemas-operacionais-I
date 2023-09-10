#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class PREPRIO : public Scheduler {
public:
    PREPRIO(CPU& _cpu) : Scheduler(_cpu) {}

    ~PREPRIO() {}

    bool execute() {}

    bool check_preemption(Process processo_atual) {} // TODO: Implementar preempção

    void organize_ready_queue(queue<Process> new_queue) {}
};
