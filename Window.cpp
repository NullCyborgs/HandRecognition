#include"Window.h"
#include<iostream>
using namespace cv;
using namespace std;
using namespace HandRecognition;

Window::Window(string id, unsigned int width, unsigned int height){
	_id = id;
	_width = width;
	_height = height;
	_frame = Mat(_width,_height, CV_8UC3);
	initIn = false;
	init();
}
Window::Window(){
	_id = "";
	_width = 0;
	_height = 0;
	initIn = false;
}
Window::~Window(){
	destroyWindow(_id);
}

string Window::getID(){
	return _id;
}

unsigned int Window::getHeight(){
	return _height;
}

unsigned int Window::getWidth(){
	return _width;
}

void Window::setWidth(unsigned int val){
	_width = val;
}

void Window::setHeight(unsigned int val){
	_height = val;
}

void Window::init(){
	namedWindow(_id, CV_WINDOW_KEEPRATIO);
	resize();
	initIn = true;
}

void Window::resize(){
	resizeWindow(_id, _width, _height);
}

void Window::update(){
	if (_frame.cols>0)
		imshow(_id, _frame);
	//resize();
}
void Window::show(Mat frame){
	if (frame.cols>0)
		_frame = frame.clone();
	//update();
}
bool Window::isInit(){
	return initIn;
}