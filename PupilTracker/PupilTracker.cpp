#include "PupilTracker.h"
#include <sstream>
#include <unistd.h>
using namespace std;

PupilTracker::PupilTracker(int port)
{
	mPort = port;
}

int main(int argc, char** argv)
{
	//  Prepare our context and publisher
	zmq::context_t context(1);

	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:5565");
	std::string msg;

	int x = 10;
	int y = 11;
	int frameId = 0;
	
	ostringstream convert;
	//int i = 4;
	//std::string text = "Player ";
	//text += std::to_string(i);

	bool keepProcessing = true;
	while (keepProcessing)
	{
		//process frame and gather data
		x++;
		y++;
		frameId++;

		//send gaze data
		msg = "GazeData";
		s_sendmore(publisher, msg);
		std::cout << "sending "<< msg << std::endl;

		msg = "x = ";
		convert.str("");
		convert << x;
		msg += convert.str();
 		s_sendmore(publisher, msg);
		std::cout << "sending " << msg << std::endl;

		msg = "y = ";
		convert.str("");
		convert << y;
		msg += convert.str();
		s_send(publisher, msg);
		std::cout << "sending " << msg << std::endl;
		
		//send frame data
		msg = "FrameData";
		s_sendmore(publisher, msg);
		std::cout << "sending " << msg << std::endl;

		msg = "frameId = ";
		convert.str("");
		convert << frameId;
		msg += convert.str();
		s_send(publisher, msg);
		std::cout << "sending " << msg << std::endl;

		//send only 10 messages per second.
		sleep(1);
		if (frameId == 50)
			keepProcessing = false;
	}

	return 0;
}

void PupilTracker::processFrame()
{
}
void PupilTracker::findPupilData()
{

}
