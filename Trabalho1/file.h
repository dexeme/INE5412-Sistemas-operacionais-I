#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;

class File
{
public:
    File();
    ~File();
    void read_file();
    void print_processes_params();

private:
    vector<ProcessParams*> processes;
    ifstream myfile;
};

#endif
