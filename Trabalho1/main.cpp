#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "file.h"
#include "process.h"

using namespace std;

int main() {
    File f;
    f.read_file();
    f.print_processes_params();
    return 0;
}
