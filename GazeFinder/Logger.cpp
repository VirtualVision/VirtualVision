#include "Logger.h"
#include "PubSocket.h"

using namespace std;


Logger::Logger()
{
	exists = false;
}

Logger::~Logger()
{

}

void Logger::makeFile()
{
	string fnameOG = "log";
	string fname = "log";
	int nextFile = 2;

	while (!exists)
	{
		if (std::ifstream(fname + ".txt"))
		{
			//std::cout << "File already exists" << std::endl;
			fname = fnameOG + to_string(nextFile);

			nextFile++;
		}
		else
		{
			exists = true;
			break;
		}

	}

	filename = fname + ".txt";
}

void Logger::log(string data)
{
	//Append the log data to log.txt
	ofstream out(filename, ios::app);
	out << data;
	//Send the log data to the user display
	pub.publishLog(data);
}