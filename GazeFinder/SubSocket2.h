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

void subscribe();

class SubSocket2
{
public:
	SubSocket2();
	~SubSocket2();
	void subscribe();
};
