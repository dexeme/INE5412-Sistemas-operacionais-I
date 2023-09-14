# Nome do programa de saída
TARGET = saida

# Compilador C++
CC = g++

# Opções de compilação
CFLAGS = -Wall -g

# Lista de arquivos fonte
SRCS = main.cpp ARM.cpp context.cpp FCFS.cpp file.cpp intel.cpp kernel.cpp output.cpp PREPRIO.cpp PRIO.cpp process.cpp RR.cpp SJF.cpp

# Lista de arquivos de cabeçalho
HEADERS = context.h CPU.h file.h kernel.h process_params.h process.h scheduler.h

build:
	g++ main.cpp -o bin/saida

# Default é o FCFS
default-run:
	./bin/saida 0

default-all: build default-run