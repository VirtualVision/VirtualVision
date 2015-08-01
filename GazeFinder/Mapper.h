#ifndef _MAPPER_
#define _MAPPER_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <cstdio>
#include <opencv/highgui.h>
#include "PubSocket.h"
#include "Logger.h"

#define SIZE 9

using namespace std;

class Mapper
{
public:
	Logger dataLog;
	PubSocket pub;
	Mapper();
	~Mapper();
	void connect();
	void setLogger(Logger d);
	void setPub(PubSocket p);
	void homography_map_point(double map_matrix[3][3], CvPoint p);
};

#endif