#ifndef _PUBSOCKET_
#define _PUBSOCKET_

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <zmq.hpp>
#include "zhelpers.hpp"
#include <windows.h>

using namespace std;

class PubSocket
{
private:
	int mPort;
public:

	PubSocket();
	~PubSocket();
	void connect();
	void publishPoints(int x, int y);
	void publishLog(string data);
};

#endif