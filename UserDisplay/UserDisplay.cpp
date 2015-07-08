#include "UserDisplay.h"

using namespace std;

UserDisplay::UserDisplay()
{
}

int main(int argc, char** argv)
{
	UserDisplay *controller = new UserDisplay();

	zmq::context_t context(1);

	//  Connect our subscriber socket
	zmq::socket_t subscriber(context, ZMQ_SUB);

	subscriber.setsockopt(ZMQ_SUBSCRIBE, "FrameData", 8);
	subscriber.connect("tcp://169.254.0.10:5565");

	while (1) {

		std::string msg = s_recv(subscriber);
		std::cout << "got " << msg << std::endl;

	}
	
	return 0;
}
