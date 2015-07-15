#ifndef _CALIBRATOR_
#define _CALIBRATOR_

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
#include <string>

class Calibrator
{
public:
	Calibrator();
	~Calibrator();
	// CvPoint is 'integer', I need 'double'
	typedef struct stuDPoint
	{
		double x;
		double y;
	}stuDPoint;
	void setX(double x);
	void setY(double y);
	void calibrate();
	void cal_calibration_homography(double xtargets[], double ytargets[], double xpupil[], double ypupil[]);
	stuDPoint* normalize_point_set(stuDPoint* point_set, double &dis_scale, stuDPoint &nor_center, int num);
	void svd(int m, int n, double **a, double **p, double *d, double **q);
	void matrix_multiply33(double a[][3], double b[][3], double r[][3]);
	void affine_matrix_inverse(double a[][3], double r[][3]);
	void homography_map_point(double x, double y);
};

#endif