#include "Display.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	Display *display = new Display();	
	QMainWindow *displayWindow = new QMainWindow();







	
	display->show();

    return a.exec();
}