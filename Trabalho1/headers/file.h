#ifndef FILE_H
#define FILE_H

#include "../headers/process.h"


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class File
{
public:
	File();
	~File();
	void read_file(string file_name);
	void print_processes_params();
};

#endif