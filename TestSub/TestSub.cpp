
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
	subscriber.connect("tcp://localhost:5569");

	int counter = 0;
	int rows = 0;
	int cols = 0;
	int * pRows;
	int * pCols;
	size_t size;
	int rc;
	Mat  img = Mat::zeros(rows, cols, CV_8UC3);
	int iSize;

	while (1) 
	{
		try
		{
		rc = zmq_msg_init(&msg);		
		rc = zmq_msg_recv(&msg, subscriber, 0);
		
		if (counter == 0)
		{		
			//extract x
			size = zmq_msg_size(&msg);
			//cast to regular int
			iSize = static_cast<int>(size);

			pRows = new int[iSize];

			memcpy(pRows, (int *)zmq_msg_data(&msg), iSize * sizeof(int));

			rows = *pRows;

			std::cout << "receiving " << rows << " rows" << std::endl;

			counter++;
		}
		else if (counter == 1)
		{
			//extract y
			size = zmq_msg_size(&msg);
			//cast to regular int
			iSize = static_cast<int>(size);

			pCols = new int[iSize];

			memcpy(pCols, (int *)zmq_msg_data(&msg), iSize * sizeof(int));

			cols = *pCols;

			std::cout << "receiving " << cols << " cols" << std::endl;

			counter++;
		}
		else
		{
			std::cout << "image" << std::endl;
			std::cout << "received rows = " << rows << " cols = " << cols << std::endl;
			//get size of message (image)
			size = zmq_msg_size(&msg);
			//cast to regular int
			iSize = static_cast<int>(size);
			//get uchar image data from message
			uchar* sockData;
		
			sockData = new uchar[iSize];
				
			memcpy(sockData, (uchar*)zmq_msg_data(&msg), iSize * sizeof(uchar));

			zmq_msg_close(&msg);


			img = Mat::zeros(rows, cols, CV_8UC3);

			int ptr = 0;

			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols; j++)
				{

					img.at<Vec3b>(i, j) = Vec3b(sockData[ptr + 0], sockData[ptr + 1], sockData[ptr + 2]);
					ptr = ptr + 3;
				}
			}

			delete[] pRows;
			pRows = nullptr;
			delete[] pCols;
			pCols = nullptr;
			delete[] sockData;
			sockData = nullptr;

			counter = 0;

			}
		}
		catch (std::bad_alloc& ba)
		{
			std::cout << "bad_alloc caught: " << ba.what() << '\n';
		}
		
	}


//	waitKey(0);
	

	return 0;
}
