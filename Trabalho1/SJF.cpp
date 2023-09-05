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

    void organize_ready_queue() {
        vector<Process> processos;
        while (!is_ready_queue_empty()) {
            processos.push_back(get_next_process());
        }
        sort(processos.begin(), processos.end(), [](Process a, Process b) {
            return a.getDuration() < b.getDuration();
        });
        for (Process processo : processos) {
            add_process(processo);
        }
    }



};