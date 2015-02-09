#include "HR_Main.h"
#include "WindowManager.h"
#include"TrafficOfficer.h"
#include<opencv2\highgui\highgui.hpp>
#include<iostream>
#include<queue>
#include"ImgToken.h"
#include<Windows.h>
#include<conio.h>
using namespace std;
using namespace cv;
using namespace HandRecognition;
#define online
//#define offline
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
#ifdef online
	VideoCapture cap(0);
	waitKey(1000);
	if (!cap.isOpened()){
		cout << "Failed to launch camera\n";
		return;
	}
	_cameraWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	_cameraHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
#endif
#ifdef offline
	Mat orgImg = imread("E:/Samples/Right Hand/RH1_5.jpg");
	pyrDown(orgImg, orgImg);
	pyrDown(orgImg, orgImg);
	//pyrDown(orgImg, orgImg);
	_cameraWidth = orgImg.cols;
	_cameraHeight = orgImg.rows;
#endif

	WindowManager::addWindow(WindowPtr(new Window("main",_cameraWidth,_cameraHeight)), true);
	WindowManager::addWindow(WindowPtr(new Window("Original", _cameraWidth, _cameraHeight)));
	WindowManager::addWindow(WindowPtr(new Window("tracks",400,400)));
	//WindowManager::addWindow(Window("debug", _cameraWidth, _cameraHeight));
	int BMin = 0, BMax = 200, GMin = 0, GMax = 100, RMin = 0, RMax = 255;
	createTrackbar("BMin", "tracks", &BMin, 255);
	createTrackbar("BMax", "tracks", &BMax, 255);
	createTrackbar("GMin", "tracks", &GMin, 255);
	createTrackbar("GMax", "tracks", &GMax, 255);
	createTrackbar("RMin", "tracks", &RMin, 255);
	createTrackbar("RMax", "tracks", &RMax, 255);

	launchThreads();

	while (1){
		ImgToken img, res;
#ifdef online
		bool successFrameRead = cap.read(img.original);
#endif
#ifdef offline
		bool successFrameRead = true;
		img.original = orgImg.clone();
#endif
		if (!successFrameRead){
			cout << "Failed to read a frame\n";
		}
		else{
			TrafficOfficer::pushProcessingQueue(img);
			//WindowManager::show(frame);
		}
		if (TrafficOfficer::peekViewQueue()){
			/*if (res)
				res = nullptr;*/
			res = TrafficOfficer::popViewQueue();
		}
		if (res.contour.cols > 0){
			WindowManager::show(res.contour);
			WindowManager::show(res.original, "Original");
		}
		WindowManager::update();
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
		Sleep(50);
	}
	//cleaning the traffic
	TrafficOfficer::cleanUp();
}

void HR_Main::launchThreads(){
	//launch first thread
	_processorThread = new thread(&FrameProcessor::process, _frameProcessor);
	_detectorThread = new thread(&HandDetector::detect, _handDetector);
}