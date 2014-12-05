#include"WindowManager.h"
using namespace HandRecognition;
using namespace std;
using namespace cv;
map<string, WindowPtr> WindowManager::_windowMap = map<string, WindowPtr>();
WindowPtr WindowManager::_mainWindow = nullptr;
void WindowManager::show(Mat frame, string id){
	if (id != ""){
		auto win = _windowMap.find(id);
		if (win != _windowMap.end()){
			win->second->show(frame);
		}
	}
	else{
		if (_mainWindow){
			_mainWindow->show(frame);
		}
	}
}
void WindowManager::removeWindow(string id){
	auto win = _windowMap.find(id);
	if (win != _windowMap.end())
		_windowMap.erase(win);
}
void WindowManager::addWindow(WindowPtr win, bool main){
	if (main)
		_mainWindow = win;
	_windowMap[win->getID()] = win;
}
void WindowManager::update(){
	for (auto win : _windowMap)
		win.second->update();
}
void WindowManager::cleanUp(){
	_windowMap.clear();
	_mainWindow = nullptr;
}