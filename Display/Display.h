#ifndef DISPLAY_H
#define DISPLAY_H

#include <QMainWindow>
#include <QApplication>
#include "ui_Display.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>


#include <zmq.hpp>
#include "zhelpers.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>

using namespace cv;
using namespace zmq;
using namespace std;

class Display : public QMainWindow
{
	Q_OBJECT

public:
	explicit Display(QWidget *parent = 0);	
	~Display();
	zmq_msg_t msg;

public slots:
	void subscribeTracker();
	void subscribeLog();
	void MyTimerSlot();
	void MyTimerSlot2();
	
private:
	Ui::Display ui;
	int counter;
	int rows;
	int cols;
	Mat img;
	// int * pRows;
	//  int * pCols;
	uchar* sockData;
	//  const uchar *qImageBuffer;
	QGraphicsScene *scene;
	QPixmap image;
	QTimer *imageTimer;
	QTimer *logTimer;
	QImage  q;
	QGraphicsPixmapItem* pixmapItem;

	context_t context;	
};

#endif // DISPLAY_H
