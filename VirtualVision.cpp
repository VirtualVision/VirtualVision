#include <stdio.h>
#include <stdlib.h>


/** @function main */
int main(int argc, char** argv)
{
	#ifdef WIN32

	//system("start C:\\build\\GazeFinder\\Debug\\GazeFinder.exe");
	//system("start C:\\build\\PupilTracker\\Debug\\PupilTracker.exe");
	//system("start C:\\build\\GameEnv\\Debug\\GameEnv.exe");
	//system("start C:\\build\\UserDisplay\\Debug\\UserDisplay.exe");
	system("start C:\\build\\TestPub\\Debug\\TestPub.exe");
	system("start C:\\build\\TestSub\\Debug\\TestSub.exe");

	#else

	#endif
	return 0;
}