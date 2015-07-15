#include "PubSocket.h"
#include "Logger.h"
#include <string>

using namespace std;

//  Prepare our context and publisher
zmq::context_t context(1);

zmq::socket_t publisher(context, ZMQ_PUB);

Logger log1;

PubSocket::PubSocket(int port)
{
	mPort = port;

}

PubSocket::~PubSocket()
{
}

void PubSocket::connect()
{
	
	publisher.bind("tcp://*:5568");
	
}


void PubSocket::publishPoints(int x, int y)
{
	std::string msg;
	//send gaze data
	msg = "ScreenPoints";
	s_sendmore(publisher, msg);
	std::cout << "sending " << msg << std::endl;
	log1.log("sending: ");
	log1.log(msg);
	log1.log("\n");

	msg = "";
	msg += std::to_string(x);
	s_sendmore(publisher, msg);
	std::cout << "sending " << msg << std::endl;
	log1.log("sending: ");
	log1.log(msg);
	log1.log("\n");

	msg = "";
	msg += std::to_string(y);
	s_send(publisher, msg);
	std::cout << "sending " << msg << std::endl;
	log1.log("sending: ");
	log1.log(msg);
	log1.log("\n\n");

}

void PubSocket::publishLog(string data)
{
	std::string msg;
	msg = "DataLog";
	s_sendmore(publisher, msg);
	//std::cout << "sending " << msg << std::endl;


	msg = "";
	msg += data;
	s_sendmore(publisher, msg);
	//std::cout << "sending " << msg << std::endl;

}