#include"TrafficOfficer.h"
using namespace std;
using namespace cv;
using namespace HandRecognition;
std::queue<cv::Mat> TrafficOfficer::_processingQueue = queue<cv::Mat>();
std::queue<cv::Mat> TrafficOfficer::_detectingQueue = queue<cv::Mat>();

bool TrafficOfficer::peekDetectingQueue(){
	if (_detectingQueue.size() > 0)
		return true;
	return false;
}
bool TrafficOfficer::peekProcessingQueue(){
	if (_processingQueue.size() > 0)
		return true;
	return false;
}

Mat TrafficOfficer::popDetectingQueue(){
	auto res = _detectingQueue.front();
	_detectingQueue.pop();
	return res;
}
Mat TrafficOfficer::popProcessingQueue(){
	auto res = _processingQueue.front();
	_processingQueue.pop();
	return res;
}

void TrafficOfficer::pushDetectingQueue(Mat& frame){
	_detectingQueue.push(frame);
}

void TrafficOfficer::pushProcessingQueue(Mat& frame){
	_processingQueue.push(frame);
}

void TrafficOfficer::cleanUp(){
	while (_processingQueue.empty())
		_processingQueue.pop();
	while (_detectingQueue.empty())
		_detectingQueue.pop();
}