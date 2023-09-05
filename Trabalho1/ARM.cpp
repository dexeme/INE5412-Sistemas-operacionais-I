#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

#include "process.h"
#include "CPU.h"


using namespace std;

class ARM : public CPU {
public:
    ARM() : CPU() {}

    ~ARM() {}

    void virtual run_process(Process processo) {}
    void virtual save_context(Process processo) {}
    void virtual restore_context(Process processo) {}
    void virtual switch_context(Process processo_atual, Process processo_novo) {}
    
};
