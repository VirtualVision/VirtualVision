
#include "TestPub.h"
using namespace cv;
using namespace zmq;
using namespace std;

TestPub::TestPub(int port)
{
	mPort = port;
}

int main(int argc, char** argv)
{
	
	//  Prepare our context and publisher
	context_t context(1);
	socket_t publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:5567");



	// OPENCV mat object
	Mat image;
	/// Load an image
	image = imread("C:\\VirtualVision\\Images\\Penguins.jpg");
	/// Show the image
	imshow("TestPub Window", image);


	//create message
	zmq_msg_t msg;
	int image_size = image.total() * image.elemSize();
	uchar * image_uchar = new uchar[image_size];	
	std::memcpy(image_uchar, image.data, image_size * sizeof(uchar));
	int rc = zmq_msg_init_size(&msg, image_size * sizeof(uchar));
	if (rc == 0)
	{
		cout << "message init was sucessful!!!! " << endl;
		////////////////////////////////////////////////////////////////////
		memcpy(zmq_msg_data(&msg), image_uchar, image_size * sizeof(uchar));

		cout << "converted size = " << image_size * sizeof(uchar) << endl;
		rc = zmq_msg_send(&msg, publisher, 0);
		if (rc == -1)
		{
			cout << "message send was unsucessful!!!! " << endl;
		}
		else
		{
			cout << "message send was sucessful!!!! " << endl;
			cout << "message size sent was " << rc << endl;
		}
	}
	else
	{
		cout << "message init was unsucessful!!!! " << endl;		
	}
		

	/// Wait until user exit program by pressing a key
	waitKey(0);

	return 0;
}


//zmq_msg_t message;
//zmq_msg_init_size(&message, strlen(string));
//memcpy(zmq_msg_data(&message), string, strlen(string));
//rc = zmq_send(socket, &message, 0);