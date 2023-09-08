#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

#include "kernel.cpp"
#include "kernel.h"

using namespace std;

int main() {
    Kernel kernel;
    kernel.start();
}
