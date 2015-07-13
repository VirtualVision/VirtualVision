#include "Logger.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


Logger::Logger()
{
}


Logger::~Logger()
{
}

void Logger::log(string data)
{
	ofstream out("log.txt", ios::app);
	out << data;
	//out.close();
}