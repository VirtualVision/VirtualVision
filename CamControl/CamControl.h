
#include <iostream>

class CamControl
{
private:


public:
	CamControl();
	~CamControl(){};
	void hello();
	bool isCmaeraOn();
	void turnCameraOff();
	void turnCameraOn();
	void startRecording();
	void endRecording();

	bool isLightOn();
	void turnLightOn();
	void turnLightOff();
};