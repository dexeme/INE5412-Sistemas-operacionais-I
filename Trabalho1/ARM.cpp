#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class ARM : public CPU {
public:
    ARM() {}

    ~ARM() {}

    void virtual run_process() {}
    void virtual save_context() {}
    void virtual restore_context() {}
    void virtual switch_context() {}
    
};
