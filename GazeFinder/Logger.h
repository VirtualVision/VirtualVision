#ifndef _LOGGER_
#define _LOGGER_
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Logger
{
public:
	Logger();
	~Logger();
	void log(string data);
};

#endif