#include<iostream>
#include"HR_Main.h"
#include<opencv2\highgui\highgui.hpp>
using namespace HandRecognition;
using namespace std;
using namespace cv;
int main(){
	cout << "Hello, World!!!" << endl;
	HR_Main hr;
	hr.Main();


	//VideoCapture cap(0);
	//waitKey(1000);
	//if (!cap.isOpened()){
	//	cout << "Failed to launch camera\n";
	//	return 0;
	//}
	//Mat frame;
	//while (1){
	//	bool successFrameRead = cap.read(frame);
	//	if (!successFrameRead || frame.data[0] == '\0'){
	//		cout << "Failed to read a frame\n";
	//	}
	//	vector<vector<Point> > contours;
	//	vector<Vec4i> h;
	//	//Mat res = frame->clone();
	//	Mat res;
	//	frame.copyTo(res);
	//	findContours(res, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//	if (waitKey(30) == 27){
	//		cout << "User pressed esc\n";
	//		break;
	//	}
	//}

	return 0;
}