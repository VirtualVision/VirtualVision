#include "PupilTracker.h"

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

	int x = 100;
	int y = 110;
	int frameId = 0;

	int i = 4;
	std::string text = "Player ";
	text += std::to_string(i);

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

		msg = "";
		msg += std::to_string(x);
		s_sendmore(publisher, msg);
		std::cout << "sending " << msg << std::endl;

		msg = "";
		msg += std::to_string(y);
		s_send(publisher, msg);
		std::cout << "sending " << msg << std::endl;
		
		//send frame data
		msg = "FrameData";
		s_sendmore(publisher, msg);
		std::cout << "sending " << msg << std::endl;

		msg = "frameId = ";
		msg += std::to_string(frameId);
		s_send(publisher, msg);
		std::cout << "sending " << msg << std::endl;

		//send only 10 messages per second.
		_sleep(100);
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