#include "HR_Main.h"
#include "WindowManager.h"
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;
using namespace HandRecognition;

HR_Main::HR_Main() {
	_cameraWidth = _cameraHeight = 0;
}

HR_Main::~HR_Main(){
	_processorThread.detach();
	_detectorThread.detach();
}

void HR_Main::Main(){
	VideoCapture cap(0);
	if (!cap.isOpened()){
		cout << "Failed to launch camera\n";
		return;
	}
	_cameraWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	_cameraHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	WindowManager::addWindow(WindowPtr(new Window("main",_cameraWidth,_cameraHeight)), true);

	while (1){
		Mat frame;
		bool successFrameRead = cap.read(frame);
		if (!successFrameRead){
			cout << "Failed to read a frame\n";
			break;
		}
		launchThreads();
		WindowManager::show(frame);
		if (waitKey(30) == 27){
			cout << "User pressed esc\n";
			break;
		}
	}
}

void HR_Main::launchThreads(){
	//launch first thread
	//_processorThread = thread(FUNCTION, object);
	//_detectorThread = thread(FUNCTION, object);
}