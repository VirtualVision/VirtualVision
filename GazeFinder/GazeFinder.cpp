#include "GazeFinder.h"

using namespace std;

GazeFinder::GazeFinder()
{
}

int main(int argc, char** argv)
{
	GazeFinder *controller = new GazeFinder();
	zmq::context_t context(1);

	//  Connect our subscriber socket
	zmq::socket_t subscriber(context, ZMQ_SUB);

	subscriber.setsockopt(ZMQ_SUBSCRIBE, "GazeData", 8);
	subscriber.connect("tcp://localhost:5565");

	while (1) {
		
		std::string msg = s_recv(subscriber);
		std::cout << "got " << msg << std::endl;

	}

	return 0;
}
