#include <iostream>
#include <stdio.h>
#include <stdlib.h>


#include <zmq.hpp>
#include "zhelpers.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class TestSub
{
private:
	int mPort;

public:
	TestSub(int port);
	~TestSub(){};
	
};