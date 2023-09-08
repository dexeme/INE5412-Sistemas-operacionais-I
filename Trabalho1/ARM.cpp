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
    ARM() {}

    ~ARM() {}

    void run_process(Process processo) override {}
    void save_context(Process processo) override {
        
    }
    void restore_context(Process processo) override {}
    void switch_context(Process processo_atual, Process processo_novo) override {}
    
};
