#ifdef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <CamControl.h>
#include "VirtualVisionConfig.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <zmq.hpp> 
#include <iostream>
#include <thread>
#include <chrono>
#else
#include <stdio.h>
#include <stdlib.h>
#include <CamControl.h>
#include "VirtualVisionConfig.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <zmq.hpp> 
#include <iostream>
#include <pthread.h>
#include <chrono>
#endif




#ifdef WIN32
void camControl1()
{
	int count = 0;
	CamControl *camControl = new CamControl();
	while (count < 5)
	{
		camControl->hello();
		count++;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}
void camControl2()
{
	int count = 0;
	CamControl *camControl = new CamControl();
	while (count < 10)
	{
		camControl->world();
		count++;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
#else
void camControl1()
{
	int count = 0;
	CamControl *camControl = new CamControl();
	while (count < 5)
	{
		camControl->hello();
		count++;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}
void camControl2()
{
	int count = 0;
	CamControl *camControl = new CamControl();
	while (count < 10)
	{
		camControl->world();
		count++;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
#endif

/** @function main */
int main(int argc, char** argv)
{
#ifdef WIN32
	//test for build and compile linkage to OpenCV
	cv::Mat gray;
	//test for build and compile linkage to ZeroMQ
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	socket.bind("tcp://*:5555");

	std::thread t1(camControl1), t2(camControl2);

	t1.join();
	t2.join();
#else
	//test for build and compile linkage to OpenCV
	cv::Mat gray;
	//test for build and compile linkage to ZeroMQ
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	socket.bind("tcp://*:5555");

	pthread_t threads[2];

	int rc;
	int i;
	for (i = 0; i < NUM_THREADS; i++){
		cout << "main() : creating thread, " << i << endl;
		rc = pthread_create(&threads[i], NULL,
			PrintHello, (void *)i);
		if (rc){
			cout << "Error:unable to create thread," << rc << endl;
			exit(-1);
		}
	}
	cout << "main() : creating thread, " << i << endl;
	rc = pthread_create(&threads[i], NULL,
		camControl1, (void)i);
	if (rc)
	{
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}

	cout << "main() : creating thread, " << i << endl;
	rc = pthread_create(&threads[i], NULL,
		camControl2, (void)i);
	if (rc)
	{
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}

#endif
	return 0;
}