
#include "TestSub.h"
using namespace cv;
using namespace zmq;
using namespace std;

TestSub::TestSub(int port)
{
	mPort = port;
}

int main(int argc, char** argv)
{
	// OPENCV mat object
	Mat imageOld;
	imageOld = imread("C:\\Users\\Public\\Pictures\\Sample Pictures\\Koala.jpg");
	//uchar * image_uchar;

	zmq_msg_t msg;
	zmq::context_t context(1);
	zmq::socket_t subscriber(context, ZMQ_SUB);

	subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
	subscriber.connect("tcp://localhost:5567");

	
	int rc = zmq_msg_init(&msg);
	//recieve zmq message
	rc = zmq_msg_recv(&msg, subscriber, 0);
	//get size of message (image)
	size_t size = zmq_msg_size(&msg);
	//cast to regular int
	int iSize = static_cast<int>(size);
	//get uchar image data from message
	uchar* sockData = (uchar*)zmq_msg_data(&msg);

	//Open cv mat to hold image
	Mat  img = Mat::zeros(768, 1024, CV_8UC3);

	//Copy data to Mat, RGBRGB...
	int ptr = 0;

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) 
		{
			img.at<Vec3b>(i, j) = Vec3b(sockData[ptr + 0], sockData[ptr + 1], sockData[ptr + 2]);
			ptr = ptr + 3;
		}
	}

	/// Show the image
	imshow("TestPub Window", img);
	/// Wait until user exit program by pressing a key
	waitKey(0);
	

	return 0;
}
