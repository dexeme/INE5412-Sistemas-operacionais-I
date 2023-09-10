#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class RR : public Scheduler {
public:
    RR(CPU& _cpu) : Scheduler(_cpu) {}

    ~RR() {}

    bool execute() {}

    bool check_preemption(Process processo_atual) {} // TODO: Implementar preempção

    void organize_ready_queue(queue<Process> new_queue) {}
};
