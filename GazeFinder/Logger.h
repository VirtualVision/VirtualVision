#ifndef _LOGGER_
#define _LOGGER_

#include <iostream>
#include <fstream>
#include <string>
#include "PubSocket.h"

using namespace std;

class Logger
{
public:
	PubSocket pub;
	string filename;
	Logger();
	~Logger();
	bool exists;
	void log(string data);
	void makeFile();
};

#endif