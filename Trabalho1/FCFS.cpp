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

    void virtual execute() {}

    void virtual organize_ready_queue() {
        // não precisa organizar a fila de prontos
    }
};
