#include "GazeFinder.h"
#include "Mapper.h"
#include "Calibrator.h"
#include "Logger.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <zmq.hpp>
#include "zhelpers.hpp"
#include <time.h>
#include <thread>

using namespace std;

zmq::context_t context2(1);

zmq::socket_t subscriber3(context2, ZMQ_SUB);
zmq::socket_t subscriber4(context2, ZMQ_SUB);
zmq::socket_t subscriber5(context2, ZMQ_SUB);

volatile bool calibrated = false;

Logger dataLog;
PubSocket p;
Calibrator c;

void task1(string msg);
void connect();
void subscribe(Calibrator c);
void runMapper(Calibrator c);

int main(int argc, char** argv)
{
	dataLog.makeFile();

	p.connect();				//connect our publisher

	c.setLogger(dataLog);		//set the log
	c.setPub(p);			//set the publisher

	int counter = 0;			//count how many calibration points received

	connect();

		while (1)
		{

			subscribe(c);		//listen for a calibration point
			counter++;			

			if (counter >= 9)	//if all points received
			{
				c.calibrate();				//calculate calibration matrix
				calibrated = true;			//calibration is complete
				counter = 0;				//reset counter in case of recalibration
				thread t1(runMapper, c);	//start sending the screen points to the oculus
				t1.detach();				//detach the thread
			}
		}
	
	return 0;
}

/*
*  Connect to the pupil tracker and the oculus
*/
void connect()
{

	subscriber3.setsockopt(ZMQ_SUBSCRIBE, "GazeData", 8);
	subscriber4.setsockopt(ZMQ_SUBSCRIBE, "Calibrate", 9);
	subscriber5.setsockopt(ZMQ_SUBSCRIBE, "GazeData", 8);

	subscriber3.connect("tcp://localhost:5565");
	//subscriber.connect("tcp://192.168.1.105:5565");
	subscriber4.connect("tcp://localhost:5567");
	subscriber5.connect("tcp://localhost:5565");
}


/*
*  Get pupil points and convert to screen points
*/

void runMapper(Calibrator c)
{

	//Stop if recalibration is in progress
	while(calibrated)
	{
		std::string msg2 = "";
		std::string msg3 = "";
		std::string msg4 = "";
		int b = 1;
		while (b)
		{
			msg2 = s_recv(subscriber5);
			std::cout << "got " << msg2 << std::endl;
			msg3 = s_recv(subscriber5);
			std::cout << "got " << msg3 << std::endl;
			msg4 = s_recv(subscriber5);
			std::cout << "got " << msg4 << std::endl;
			if (atof(msg3.c_str()) != 0.0 && atof(msg4.c_str()) != 0.0) {
				b = 0;
			}
		}

		cout << "To be mapped: " << msg3 << ", " << msg4 << endl;
		dataLog.log("To be mapped: " + msg3 + ", " + msg4 + "\n");

		//Send to the mapper to map to screen points
		c.homography_map_point(atof(msg3.c_str()), atof(msg4.c_str()));
	}
}

/*
*  Listen for signal to calibrate. Send pupil coordinates to Calibrator
*  for each calibrate signal received. 
*/

void subscribe(Calibrator c)
{
	
		//Listen for calibration signal from Oculus
		string msg = s_recv(subscriber4);
		cout << "got " << msg << endl;
		dataLog.log("got " + msg + "\n");

		//Check if already calibrated
		if (calibrated)
		{
			//If already calibrated then begin a new calibration
			cout << "New Calibration" << endl;
			dataLog.log("Beginning new calibration\n");
			calibrated = false;
			//Set the counter in Calibrator back to zero
			c.recalibrate();
			
		}

		string msg2 = "";
		string msg3 = "";
		string msg4 = "";

		int b = 1;

		//Receive pupil coordinates from tracker
		while (b)
		{
			msg2 = s_recv(subscriber3);
			cout << "got " << msg2 << endl;
			msg3 = s_recv(subscriber3);
			cout << "got " << msg3 << endl;
			msg4 = s_recv(subscriber3);
			cout << "got " << msg4 << endl;

			//Reject if a zero value is received
			if (atof(msg3.c_str()) != 0.0 && atof(msg4.c_str()) != 0.0) 
			{
				b = 0; //Accept if no zeros
			}
		}

		cout << "Trying to add x: " << msg3.c_str() << endl;
		dataLog.log("Trying to add x : " + msg3 + "\n");

		//Send to the Calibrator
		c.setX(atof(msg3.c_str()));

		cout << "Trying to add y: " << msg4.c_str() << endl;
		dataLog.log("Trying to add x : " + msg4 + "\n");

		c.setY(atof(msg4.c_str()));

}