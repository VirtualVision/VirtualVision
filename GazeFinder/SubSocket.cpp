#include "SubSocket.h"
#include "Calibrator.h"
#include "Logger.h"
using namespace std;

Logger log5;

SubSocket::SubSocket()
{
}


SubSocket::~SubSocket()
{
}

void SubSocket::subscribe(Calibrator c)
{
	int counter = 0;

	zmq::context_t context(1);

	//  Connect our subscriber socket
	zmq::socket_t subscriber(context, ZMQ_SUB);
	zmq::socket_t subscriber2(context, ZMQ_SUB);


	subscriber.setsockopt(ZMQ_SUBSCRIBE, "GazeData", 8);
	subscriber2.setsockopt(ZMQ_SUBSCRIBE, "Calibrate", 9);

	subscriber.connect("tcp://localhost:5565");
	subscriber2.connect("tcp://localhost:5567");

	while (1) {

		std::string msg = s_recv(subscriber2);
		std::cout << "got " << msg << std::endl;
		std::string msg2 = s_recv(subscriber);
		std::cout << "got " << msg2 << std::endl;
		std::string msg3 = s_recv(subscriber);
		std::cout << "got " << msg3 << std::endl;
		std::string msg4 = s_recv(subscriber);
		std::cout << "got " << msg4 << std::endl;

		std::cout << "Trying to add x: " << msg3.c_str() << std::endl;
		log5.log("Trying to add x : ");
		log5.log(msg3);
		log5.log("\n");

		c.setX(atof(msg3.c_str()));

		std::cout << "Trying to add y: " << msg4.c_str() << std::endl;
		log5.log("Trying to add x : ");
		log5.log(msg4);
		log5.log("\n");

		c.setY(atof(msg4.c_str()));

		std::cout << counter << std::endl;
		counter++;

		if (counter >= 9)
		{
			cout << "Beginning Calibration" << endl;
			log5.log("Beginning Calibration\n");
			c.calibrate();
			break;
		}

	}

	cout << "Switching to pupil to screen mapping" << endl;
	log5.log("Switching to pupil to screen mapping\n\n");

	while (1)
	{

		std::string msg = s_recv(subscriber);
		std::cout << "got " << msg << std::endl;
		std::string msg2 = s_recv(subscriber);
		std::cout << "got " << msg2 << std::endl;
		std::string msg3 = s_recv(subscriber);
		std::cout << "got " << msg3 << std::endl;

		cout << "To be mapped: " << msg2 << ", " << msg3 << endl;
		log5.log("To be mapped: ");
		log5.log(msg2);
		log5.log(", ");
		log5.log(msg3);
		log5.log("\n");

		c.homography_map_point(atof(msg2.c_str()), atof(msg3.c_str()));

	}
}