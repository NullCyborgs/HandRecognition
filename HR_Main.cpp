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
	WindowManager::addWindow(WindowPtr(new Window("tracks",700,400)));
	int BMin = 0, BMax = 0, GMin = 0, GMax = 0, RMin = 0, RMax = 0;
	createTrackbar("BMin", "tracks", &BMin,255);
	createTrackbar("BMax", "tracks", &BMax, 255);
	createTrackbar("GMin", "tracks", &GMin, 255);
	createTrackbar("GMax", "tracks", &GMax, 255);
	createTrackbar("RMin", "tracks", &RMin, 255);
	createTrackbar("RMax", "tracks", &RMax, 255);

	launchThreads();

	while (1){
		MatPtr frame = MatPtr(new Mat());
		MatPtr res = nullptr;
		bool successFrameRead = cap.read(*frame);
		if (!successFrameRead || frame->data[0] == '\0'){
			cout << "Failed to read a frame\n";
		}
		else{
			TrafficOfficer::pushProcessingQueue(frame);
			//WindowManager::show(frame);
		}
		if (TrafficOfficer::peekViewQueue()){
			if (res)
				res = nullptr;
			res = TrafficOfficer::popViewQueue();
		}
		if (res != nullptr)
			WindowManager::show(MatPtr(res));
		TrafficOfficer::val("BMin", BMin);
		TrafficOfficer::val("BMax", BMax);
		TrafficOfficer::val("GMin", GMin);
		TrafficOfficer::val("GMax", GMax);
		TrafficOfficer::val("RMin", RMin);
		TrafficOfficer::val("RMax", RMax);
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