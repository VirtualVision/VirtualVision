
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>


#include <VirtualVisionConfig.h>
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include <zmq.hpp>
#include "zhelpers.hpp"
#include <windows.h>

class PupilTracker
{
private:
	int mPort;

public:
	PupilTracker(int port);
	~PupilTracker(){};
	
	void processFrame();
	void findPupilData();
	
};