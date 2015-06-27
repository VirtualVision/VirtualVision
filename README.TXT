This is UTA Senior Design Team "VirtualVision".

VirtualVision is Gaze Tracking software designed to be used with the Oculus Rift VR Headset.
The host side of the application will run on Windows 7.
The remote side of the application will run on Raspian.
Cross Compilation will be configured with CMake.

Instructions:
	Host:
		- install cmake v-2.8 or greater
		- install Visual Studio 2013
		- install git
		- pull VirtualVsion ThirdParty repo to C:\
		- pull VirtualVision VirtualVision repo to C:\
		- add CMake to PATH : "C:\Program Files (x86)\CMake\bin"
		- add OpenCV to PATH : "C:\ThirdParty\Windows_x64\OpenCV\build\x64\vc12\bin"
		- add ZeroMQ to PATH : "C:\ThirdParty\Windows_x64\ZeroMQ_4.0.4\bin"
		- add Visual Studio 2013 devenv to PATH : "C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE"
		- open Windows Terminal
		- cd to "C:\" dir
		- type "mkdir build" for out-of-source build
		- cd to "build"
		- type "cmake ..\VirtualVision"
		- type "devenv VirtualVision.sln"
		- set to Debug, win32
		- build
		- set VirtualVision as "startup project"
		done and ready to run!

	Remote:
		- apt-get install camke
		- apt-get install git
		- apt-get install libopencv-dev
		- apt-get install python-opencv
		- apt-get install libtool
		- apt-get install autoconf
		- apt-get install libpthread-stubs0-dev
		- wget http://download.zeromq.org/zeromq-4.0.4.ta.gz
		- tar zxvf zeromq-4.0.4.tar.gz
		- cd zeromq-4.0.4
		- ./configure
		- make
		- sudo make install
		- sudo ldconfig
		- wget http://github.com/zeromq/cppzmq.git
		- cp zmq.hpp to include dir that contains zmq.h
		- cd to ~
		- pull repository to ~
		- mkdir build, for out-of-source build
		- cd build
		- cmake ../VirtualVision
		- make
		- ./VirtualVision



