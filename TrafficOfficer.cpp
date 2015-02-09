#include"TrafficOfficer.h"
using namespace std;
using namespace cv;
using namespace HandRecognition;
std::queue<ImgToken> TrafficOfficer::_processingQueue = queue<ImgToken>();
std::queue<ImgToken> TrafficOfficer::_detectingQueue = queue<ImgToken>();
std::queue<ImgToken> TrafficOfficer::_viewQueue = queue<ImgToken>();
std::map<std::string, float> TrafficOfficer::_valMap = map<string, float>();


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
bool TrafficOfficer::peekViewQueue(){
	if (_viewQueue.size() > 0)
		return true;
	return false;
}

ImgToken TrafficOfficer::popDetectingQueue(){
	auto res = _detectingQueue.front();
	_detectingQueue.pop();
	return res;
}
ImgToken TrafficOfficer::popProcessingQueue(){
	auto res = _processingQueue.front();
	_processingQueue.pop();
	return res;
}
ImgToken TrafficOfficer::popViewQueue(){
	auto res = _viewQueue.front();
	_viewQueue.pop();
	return res;
}

void TrafficOfficer::pushDetectingQueue(ImgToken frame){
	_detectingQueue.push(frame);
}

void TrafficOfficer::pushProcessingQueue(ImgToken frame){
	_processingQueue.push(frame);
}
void TrafficOfficer::pushViewQueue(ImgToken frame){
	_viewQueue.push(frame);
}
void TrafficOfficer::val(string key, float v){
	_valMap[key] = v;
}
float TrafficOfficer::val(string key){
	return _valMap[key];
}

void TrafficOfficer::cleanUp(){
	_processingQueue = queue<ImgToken>();
	_detectingQueue = queue<ImgToken>();
	_viewQueue = queue<ImgToken>();
	_valMap.clear();
}