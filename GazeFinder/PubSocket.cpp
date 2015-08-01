#include "PubSocket.h"

using namespace std;

//Prepare our context and publisher
zmq::context_t context(1);

zmq::socket_t publisher(context, ZMQ_PUB);

PubSocket::PubSocket()
{

}

PubSocket::~PubSocket()
{

}

void PubSocket::connect()
{
	publisher.bind("tcp://*:5568");
}

/*
* Send screen points to the Oculus.
*/

void PubSocket::publishPoints(int x, int y)
{

	string msg;
	//send gaze data
	msg = "ScreenPoints";
	s_sendmore(publisher, msg);
	cout << "sending " << msg << endl;
	//publishLog("sending " + msg + "\n");

	msg = "";
	msg += to_string(x);
	s_sendmore(publisher, msg);
	cout << "sending " << msg << endl;
	//publishLog("sending " + msg + "\n");

	msg = "";
	msg += to_string(y);
	s_send(publisher, msg);
	cout << "sending " << msg << endl;
	//publishLog("sending " + msg + "\n");

}

/*
* Send log data to the User Display.
*/

void PubSocket::publishLog(string data)
{
	
	string msg;
	msg = "DataLog";
	s_sendmore(publisher, msg);
	cout << "sending LOG: " << msg << endl;


	msg = "";
	msg += data;
	s_send(publisher, msg);
	cout << "sending LOG: " << msg << endl;
	
}