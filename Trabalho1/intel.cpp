#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class Intel : public CPU {
public:
    Intel() {}

    ~Intel() {}

    void virtual save_context() {}
    void virtual restore_context() {}
    void virtual switch_context() {}
    
};
