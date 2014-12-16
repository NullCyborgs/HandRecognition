#include "HR_Main.h"
#include "WindowManager.h"
#include"TrafficOfficer.h"
#include<opencv2\highgui\highgui.hpp>
#include<iostream>
#include<queue>
using namespace std;
using namespace cv;
using namespace HandRecognition;

HR_Main::HR_Main() {
	_cameraWidth = _cameraHeight = 0;
	_frameProcessor = new FrameProcessor();
	_handDetector = new HandDetector();
}

HR_Main::~HR_Main(){
	if (_processorThread)
		_processorThread->detach();
	if (_detectorThread)
		_detectorThread->detach();
}

void HR_Main::Main(){
	VideoCapture cap(0);
	waitKey(1000);
	if (!cap.isOpened()){
		cout << "Failed to launch camera\n";
		return;
	}
	_cameraWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	_cameraHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	WindowManager::addWindow(WindowPtr(new Window("main",_cameraWidth,_cameraHeight)), true);
	launchThreads();
	while (1){
		Mat frame;
		bool successFrameRead = cap.read(frame);
		if (!successFrameRead || frame.data[0] == '\0'){
			cout << "Failed to read a frame\n";
		}
		else{
			TrafficOfficer::pushProcessingQueue(frame.clone());
			WindowManager::show(frame);
		}
		if (waitKey(30) == 27){
			cout << "User pressed esc\n";
			break;
		}
	}
	//cleaning the traffic
	TrafficOfficer::cleanUp();
}

void HR_Main::launchThreads(){
	//launch first thread
	_processorThread = new thread(&FrameProcessor::process, _frameProcessor);
	_detectorThread = new thread(&HandDetector::detect, _handDetector);
}