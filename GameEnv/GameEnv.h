#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include <zmq.hpp>
#include "zhelpers.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;
class GameEnv
{
private:
	int mPort;

public:
	GameEnv(int port);
	~GameEnv(){};
};