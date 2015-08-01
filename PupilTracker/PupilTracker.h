#ifndef _PUPIL_
#define _PUPIL_

//#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <zmq.hpp>
//#include "zhelpers.hpp"
#include "zhelpers2.hpp"

#include <stdlib.h>
#include <stdio.h>
using namespace std;
using namespace cv;

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

#endif