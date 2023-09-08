#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <vector>

#include "process_params.h"

using namespace std;

class File
{
public:
    File();
    ~File();

    void read_file();
    vector<ProcessParams> get_processes() { return processes_params; }

private:
    vector<ProcessParams> processes_params;
    ifstream myfile;
};

#endif
