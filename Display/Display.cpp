#include "Display.h"

using namespace cv;
using namespace zmq;
using namespace std;


context_t context(1);
socket_t frameSub(context, ZMQ_SUB);
socket_t logSub(context, ZMQ_SUB);


Display::Display(QWidget *parent) :QMainWindow(parent)
{
	ui.setupUi(this);

	ui.graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scene = new QGraphicsScene(this);
	q = QImage("C:\\VirtualVision\\Images\\orange.jpg");
	scene->addPixmap(QPixmap::fromImage(q));
	ui.graphicsView->setScene(scene);
	ui.graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
	
	//connect to pupil tracker for eye image
	frameSub.setsockopt(ZMQ_SUBSCRIBE, "", 0);
	logSub.setsockopt(ZMQ_SUBSCRIBE, "DataLog", 7);
	frameSub.connect("tcp://192.168.1.105:5556");
	logSub.connect("tcp://localhost:5571");

	counter = 0;
	rows = 0;
	cols = 0;

	// create a timer
	timer = new QTimer(this);
	timer2 = new QTimer(this);

	// setup signal and slot
	connect(timer, SIGNAL(timeout()),
		this, SLOT(MyTimerSlot()));

	// setup signal and slot
	connect(timer2, SIGNAL(timeout()),
		this, SLOT(MyTimerSlot2()));

	// msec
	timer->start(1);
	timer2->start(100);
}

Display::~Display()
{
	//delete ui;
}


void Display::MyTimerSlot()
{

	int * pRows;
	int * pCols;
	uchar* sockData;
	size_t size;
	int rc;
	int iSize;

	try
	{
		rc = zmq_msg_init(&msg);
		rc = zmq_msg_recv(&msg, frameSub, 0);

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
			delete[] pRows;
			pRows = nullptr;
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
			delete[] pCols;
			pCols = nullptr;
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

			//delete[] pRows;
			//pRows = nullptr;
			//delete[] pCols;
			//    pCols = nullptr;
			delete[] sockData;
			sockData = nullptr;

			counter = 0;



			// Show the image

			counter = 0; //Reset counter

			// Create QImage with same dimensions as input Mat

			q = QImage((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
			delete scene;
			scene = new QGraphicsScene(this);
			scene->addPixmap(QPixmap::fromImage(q.rgbSwapped()));

			ui.graphicsView->setScene(scene);
			ui.graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);

		}
	}
	catch (std::bad_alloc& ba)
	{
		std::cout << "bad_alloc caught: " << ba.what() << '\n';
	}


}

void Display::MyTimerSlot2()
{
	string rec = s_recv(logSub);
	rec = s_recv(logSub);
	cout << rec << endl;
	QString qrec = QString::fromStdString(rec);

	ui.textBrowser->append(qrec);
}





