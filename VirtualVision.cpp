
#include <stdio.h>
#include <stdlib.h>
#include <CamControl.h>
#include "VirtualVisionConfig.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <zmq.hpp> 

/** @function main */
int main(int argc, char** argv)
{
	CamControl *camControl = new CamControl();
	camControl->hello();

	//test for build and compile linkage to OpenCV
	cv::Mat gray;
	//test for build and compile linkage to ZeroMQ
	zmq::context_t context(1);

	
	return 0;
}