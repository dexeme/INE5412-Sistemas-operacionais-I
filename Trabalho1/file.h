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
    vector<ProcessParams> read_file();

private:
    vector<ProcessParams> processes;
    ifstream myfile;
};

#endif
