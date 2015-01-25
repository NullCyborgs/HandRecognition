#include"Window.h"
using namespace cv;
using namespace std;
using namespace HandRecognition;

Window::Window(string id, unsigned int width, unsigned int height){
	_id = id;
	_width = width;
	_height = height;
	_frame = Mat(_width,_height, CV_8UC3);
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

void Window::update(){
	imshow(_id, _frame);
}
void Window::show(Mat frame){
	_frame = frame.clone();
	update();
}