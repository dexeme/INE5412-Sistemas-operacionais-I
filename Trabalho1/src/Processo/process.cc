#include <iostream>
#include <fstream>

#include "../headers/file.h"
#include "../headers/process.h"

using namespace std;

ProcessParams::ProcessParams(int c, int d, int p) {
    creation_time = c;
    duration = d;
    priority = p;
}

