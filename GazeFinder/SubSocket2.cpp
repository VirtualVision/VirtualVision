#include "SubSocket2.h"

SubSocket2::SubSocket2()
{
}


SubSocket2::~SubSocket2()
{
}

void SubSocket2::subscribe()
{
	zmq::context_t context(1);

	//  Connect our subscriber socket
	zmq::socket_t subscriber(context, ZMQ_SUB);

	subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

	subscriber.connect("tcp://localhost:5567");

	while (1) {

		std::string msg = s_recv(subscriber);
		std::cout << "got " << msg << std::endl;
	}
}