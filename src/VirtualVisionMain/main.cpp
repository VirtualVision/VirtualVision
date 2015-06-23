//example includes, remove in future
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <stdlib.h>
//#include <stdio.h>
#include <zmq.hpp>  //needed to define all sockets
//#include headers to needed processes

/** @function main */
int main(int argc, char** argv)
{
	//test for build and compile linkage to OpenCV
	cv::Mat gray;
	//test for build and compile linkage to ZeroMQ
	zmq::context_t context (1);

	//define sockets to be used by all processes
	//struct AppSockets{}, or something... haha

	//prepocessor condition to check OS
	#ifdef _WIN32
		//start host process1, pass in defined sockets

		//start host process2, pass in defined sockets
		//.....

	#else
		//start remote process1, pass in defined sockets

		//start remote process2, pass in defined sockets
		//...
	#endif 

	//end VirtualVision application
	return 0;
}