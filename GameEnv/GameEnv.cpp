#include "GameEnv.h"


using namespace std;

GameEnv::GameEnv(int port)
{
	mPort = port;
}

int main(int argc, char** argv)
{
	//  Prepare our context and publisher
	zmq::context_t context(1);

	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:5567");
	std::string msg;

	int x = 10;
	int y = 11;
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

		//send calibration signal
		msg = "Calibrate";
		s_send(publisher, msg);
		std::cout << "sending " << msg << std::endl;

		//send only 10 messages per second.
		_sleep(100);
		if (frameId == 10)
			keepProcessing = false;
	}

	zmq::socket_t subscriber(context, ZMQ_SUB);
	subscriber.setsockopt(ZMQ_SUBSCRIBE, "ScreenPoints", 12);
	subscriber.connect("tcp://localhost:5568");

	while (1) 
	{
		std::string msg = s_recv(subscriber);
		std::cout << "got " << msg << std::endl;
		std::string msg2 = s_recv(subscriber);
		std::cout << "got " << msg2 << std::endl;
		std::string msg3 = s_recv(subscriber);
		std::cout << "got " << msg3 << std::endl;

	}

	return 0;
}
