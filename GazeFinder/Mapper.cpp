#include "Mapper.h"
#include "PubSocket.h"
#include "Logger.h"
//#define SIZE 9

PubSocket pub(5568);
Logger log4;

using namespace std;

Mapper::Mapper()
{

}


Mapper::~Mapper()
{
}


void Mapper::connect()
{
	pub.connect();
}

void Mapper::homography_map_point(double map_matrix[3][3], CvPoint p)
{
	cout << "Mapper is mapping: " << p.x << ", " << p.y << endl;
	log4.log("Mapper is mapping: ");
	log4.log(to_string(p.x));
	log4.log(", ");
	log4.log(to_string(p.y));
	log4.log("\n");

	CvPoint p2;
	double z = map_matrix[2][0] * p.x + map_matrix[2][1] * p.y + map_matrix[2][2];
	p2.x = (int)((map_matrix[0][0] * p.x + map_matrix[0][1] * p.y + map_matrix[0][2]) / z);
	p2.y = (int)((map_matrix[1][0] * p.x + map_matrix[1][1] * p.y + map_matrix[1][2]) / z);

	cout << "Mapper results: " << p2.x << ", " << p2.y << endl;
	log4.log("Mapper results: ");
	log4.log(to_string(p2.x));
	log4.log(", ");
	log4.log(to_string(p2.y));
	log4.log("\n\n");

	pub.publish(p2.x, p2.y);
}