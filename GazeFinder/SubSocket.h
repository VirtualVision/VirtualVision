#ifndef _SUBSOCKET_
#define _SUBSOCKET_

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <VirtualVisionConfig.h>
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include <zmq.hpp>
#include "zhelpers.hpp"
#include <time.h>
#include "Calibrator.h"

//void subscribe();

class SubSocket
{
public:
	SubSocket();
	~SubSocket();
	void subscribe(Calibrator c);
};

#endif