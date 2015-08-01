
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
	publisher.bind("tcp://*:5569");
	int *rows;
	int *cols;
	
	while (1)
	{
		string rString;
		string cString;

		// OPENCV mat object
		Mat image;
		/// Load an image
		image = imread("C:\\VirtualVision\\Images\\Penguins.jpg");

		//create message
		zmq_msg_t msg;

		zmq_msg_t rmsg;
		zmq_msg_t cmsg;

		int rc;

		try
		{
			rows = &image.rows;
			cols = &image.cols;
		}
		catch (std::bad_alloc& ba)
		{
			std::cerr << "1bad_alloc caught: " << ba.what() << '\n';
		}
		
		/// Show the image
		//imshow("TestPub Window", image);

		rc = zmq_msg_init_size(&rmsg, sizeof(*rows));
		rc = zmq_msg_init_size(&cmsg, sizeof(*cols));
		memcpy(zmq_msg_data(&rmsg), rows, sizeof(*rows));
		memcpy(zmq_msg_data(&cmsg), cols, sizeof(*cols));

		rc = zmq_msg_send(&rmsg, publisher, ZMQ_SNDMORE);
		rc = zmq_msg_send(&cmsg, publisher, ZMQ_SNDMORE);

		int image_size = image.total() * image.elemSize();
		uchar * image_uchar;
		try
		{
			image_uchar = new uchar[image_size];
		}
		catch (std::bad_alloc& ba)
		{
			std::cerr << "2bad_alloc caught: " << ba.what() << '\n';
		}

		memcpy(image_uchar, image.data, image_size * sizeof(uchar));
		rc = zmq_msg_init_size(&msg, image_size * sizeof(uchar));
		if (rc == 0)
		{
			memcpy(zmq_msg_data(&msg), image_uchar, image_size * sizeof(uchar));
			rc = zmq_msg_send(&msg, publisher, 0);
		}
		else
		{
			cout << "message init was unsucessful!!!! " << endl;
		}
		zmq_msg_close(&msg);
		delete[] image_uchar;
		image_uchar = nullptr;

	}


	return 0;
}
