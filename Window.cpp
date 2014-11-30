#include"Window.h"
#include<opencv2\highgui\highgui.hpp>
using namespace cv;
using namespace std;
using namespace HandRecognition;

Window::Window(string id, unsigned int width, unsigned int height){
	_id = id;
	_width = width;
	_height = height;
	init();
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
	namedWindow(_id);
	resize();
}

void Window::resize(){
	resizeWindow(_id, _width, _height);
}