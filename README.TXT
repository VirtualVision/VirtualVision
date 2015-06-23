This is UTA Senior Design Team "VirtualVision".

VirtualVision is Gaze Tracking software designed to be used with the Oculus Rift VR Headset.
The host side of the application will run on Windows 7.
The remote side of the application will run on Raspian.
Cross Compilation will be configured with CMake.

Instructions:
	Host:
		- install cmake v-3.3 or greater
		- install Visual Studio 2013
		- install git
		- pull VirtualVision repository, perferable to C:\
		- add CMake to PATH : "C:\Program Files (x86)\CMake\bin"
		- add OpenCV to PATH : "C:\VirtualVision\ThirdParty\Windows_x64\OpenCV\build\x64\vc12\bin"
		- add ZeroMQ to PATH : "C:\VirtualVision\ThirdParty\Windows_x64\ZeroMQ_4.0.4\bin"
		- add Visual Studio 2013 devenv to PATH : "C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE"
		- open Windows Terminal
		- cd to "VirtualVision" dir
		- type "mkdir build" for out-of-source build
		- cd to "build"
		- type "cmake ..\src"
		- type "devenv VirtualVision.sln"
		- set to Debug, win32
		- build
		- set VirtualVisionMain as "startup project"
		done and ready to run!

	Remote:
		Comming Soon!