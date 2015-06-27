#include "CamControl.h"
#include <stdio.h>
#include <stdlib.h>
#include "VirtualVisionConfig.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <zmq.hpp>

using namespace std;

CamControl::CamControl()
{


}

void CamControl::hello()
{
	//test for build and compile linkage to OpenCV
	cv::Mat gray;
	//test for build and compile linkage to ZeroMQ
	zmq::context_t context(1);
	cout << "Hello!" << endl;
}
void CamControl::world()
{
	//test for build and compile linkage to OpenCV
	cv::Mat gray;
	//test for build and compile linkage to ZeroMQ
	zmq::context_t context(1);
	cout << "World!" << endl;
}

bool CamControl::isCmaeraOn()
{
	bool test = false;

	return test;
}
void CamControl::turnCameraOff()
{

}
void CamControl::turnCameraOn()
{

}
void CamControl::startRecording()
{

}
void CamControl::endRecording()
{

}
bool CamControl::isLightOn()
{
	bool test = false;

	return test;
}
void CamControl::turnLightOn()
{

}
void CamControl::turnLightOff()
{

}