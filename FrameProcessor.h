#pragma once
#include<iostream>
#include"TrafficOfficer.h"
using namespace cv;
namespace HandRecognition{
	class FrameProcessor{
	public:
		MatPtr threshold(MatPtr f){
			for (int i = 0; i < f->rows;i++)
			for (int j = 0; j < f->cols; j++){
				int B = f->data[f->channels()*(f->cols*i + j) + 0];
				int G = f->data[f->channels()*(f->cols*i + j) + 1];
				int R = f->data[f->channels()*(f->cols*i + j) + 2];
				if (R >= G&&R >= B){
					f->data[f->channels()*(f->cols*i + j) + 0] = 255;
					f->data[f->channels()*(f->cols*i + j) + 1] = 255;
					f->data[f->channels()*(f->cols*i + j) + 2] = 255;
				}else{
					f->data[f->channels()*(f->cols*i + j) + 0] = 0;
					f->data[f->channels()*(f->cols*i + j) + 1] = 0;
					f->data[f->channels()*(f->cols*i + j) + 2] = 0;
				}
			}
			return f;
		}
		void process(){
			while (true){
				MatPtr frame;
				MatPtr res = MatPtr(new cv::Mat());
				bool gotIt = false;
				//std::cout << "processing" << std::endl;
				if (TrafficOfficer::peekProcessingQueue()){
					frame = TrafficOfficer::popProcessingQueue();
					gotIt = true;
				}
				if (gotIt){
					blur(*frame, *res, Size(9, 9));
					//cvtColor(*res, *res, CV_BGR2HSV);
					//res = threshold(frame);
					int BMin = TrafficOfficer::val("BMin");
					int BMax = TrafficOfficer::val("BMax");
					int GMin = TrafficOfficer::val("GMin");
					int GMax = TrafficOfficer::val("GMax");
					int RMin = TrafficOfficer::val("RMin");
					int RMax = TrafficOfficer::val("RMax");
					inRange(*res, Scalar(BMin, GMin, RMin), Scalar(BMax, GMax, RMax), *res);
					erode(*res, *res, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
					dilate(*res, *res, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
					TrafficOfficer::pushDetectingQueue(res);
				}
			}
		}
	};
}