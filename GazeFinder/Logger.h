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
	Logger();
	~Logger();
	
	void log(string data);
};

#endif