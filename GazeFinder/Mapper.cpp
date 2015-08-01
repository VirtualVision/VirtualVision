#include "Mapper.h"
#include "PubSocket.h"
#include "Logger.h"

Mapper::Mapper()
{

}


Mapper::~Mapper()
{

}

/*
* Map pupil point to screen point and send to the Oculus.
*/

void Mapper::homography_map_point(double map_matrix[3][3], CvPoint p)
{
	cout << "Mapper is mapping: " << p.x << ", " << p.y << endl;
	dataLog.log("Mapper is mapping: " + to_string(p.x) + ", " + to_string(p.y) + "\n");

	//Use matrix to map the pupil point to a screen point
	CvPoint p2;
	double z = map_matrix[2][0] * p.x + map_matrix[2][1] * p.y + map_matrix[2][2];
	p2.x = (int)((map_matrix[0][0] * p.x + map_matrix[0][1] * p.y + map_matrix[0][2]) / z);
	p2.y = (int)((map_matrix[1][0] * p.x + map_matrix[1][1] * p.y + map_matrix[1][2]) / z);

	cout << "Mapper results: " << p2.x << ", " << p2.y << endl;
	dataLog.log("Mapper results: " + to_string(p2.x) + ", " + to_string(p2.y) + "\n");

	//Send the screen point to the Oculus
	pub.publishPoints(p2.x, p2.y);
}