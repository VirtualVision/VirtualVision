#include "Logger.h"
#include "PubSocket.h"

using namespace std;


Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::log(string data)
{
	//Append the log data to log.txt
	ofstream out("log.txt", ios::app);
	out << data;
	//Send the log data to the user display
	pub.publishLog(data);
}