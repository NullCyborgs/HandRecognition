#include"TrafficOfficer.h"
using namespace std;
using namespace cv;
using namespace HandRecognition;
std::queue<MatPtr> TrafficOfficer::_processingQueue = queue<MatPtr>();
std::queue<MatPtr> TrafficOfficer::_detectingQueue = queue<MatPtr>();
std::queue<MatPtr> TrafficOfficer::_viewQueue = queue<MatPtr>();
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

MatPtr TrafficOfficer::popDetectingQueue(){
	auto res = _detectingQueue.front();
	_detectingQueue.pop();
	return res;
}
MatPtr TrafficOfficer::popProcessingQueue(){
	auto res = _processingQueue.front();
	_processingQueue.pop();
	return res;
}
MatPtr TrafficOfficer::popViewQueue(){
	auto res = _viewQueue.front();
	_viewQueue.pop();
	return res;
}

void TrafficOfficer::pushDetectingQueue(MatPtr frame){
	_detectingQueue.push(frame);
}

void TrafficOfficer::pushProcessingQueue(MatPtr frame){
	_processingQueue.push(frame);
}
void TrafficOfficer::pushViewQueue(MatPtr frame){
	_viewQueue.push(frame);
}
void TrafficOfficer::val(string key, float v){
	_valMap[key] = v;
}
float TrafficOfficer::val(string key){
	return _valMap[key];
}

void TrafficOfficer::cleanUp(){
	_processingQueue = queue<MatPtr>();
	_detectingQueue = queue<MatPtr>();
	_viewQueue = queue<MatPtr>();
	_valMap.clear();
}