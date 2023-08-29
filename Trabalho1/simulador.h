#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "scheduler.h"

using namespace std;

class Simulador {
    private:
        Scheduler scheduler;
    public:
        Simulador() {}
        ~Simulador() {}
        void start_simulator() {}
}