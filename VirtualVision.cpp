#include <stdio.h>
#include <stdlib.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <zmq.hpp> 
#include <iostream>
#include <thread>
#include <chrono>


/** @function main */
int main(int argc, char** argv)
{
	#ifdef WIN32

	system("start C:\\build\\GazeFinder\\Debug\\GazeFinder.exe");
	system("start C:\\build\\PupilTracker\\Debug\\PupilTracker.exe");
	//system("start C:\\build\\GameEnv\\Debug\\GameEnv.exe");
	system("start C:\\build\\UserDisplay\\Debug\\UserDisplay.exe");

	#else

	#endif
	return 0;
}