
#include "SubSocket.h"
#include "SubSocket2.h"
#include "Mapper.h"
#include "Calibrator.h"

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

using namespace std;

int main(int argc, char** argv)
{
	
	SubSocket s;
	Calibrator c;

	s.subscribe(c);

	return 0;
}
