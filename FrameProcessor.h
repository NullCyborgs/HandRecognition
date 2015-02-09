#pragma once
#include<iostream>
#include"TrafficOfficer.h"
#include"WindowManager.h"
using namespace cv;
namespace HandRecognition{
	class FrameProcessor{
	public:
		void process(){
			ImgToken frame;
			while (true){
				bool gotIt = false;
				//peeking the queue
				if (TrafficOfficer::peekProcessingQueue()){
					frame = TrafficOfficer::popProcessingQueue();
					gotIt = true;
				}
				if (gotIt){
					//processing the frame
					//getting the values of the tracks
					int BMin = TrafficOfficer::val("BMin");
					int BMax = TrafficOfficer::val("BMax");
					int GMin = TrafficOfficer::val("GMin");
					int GMax = TrafficOfficer::val("GMax");
					int RMin = TrafficOfficer::val("RMin");
					int RMax = TrafficOfficer::val("RMax");
					//thresholding the img
					blur(frame.original, frame.binary, Size(9, 9));
					inRange(frame.binary, Scalar(BMin, GMin, RMin), Scalar(BMax, GMax, RMax), frame.binary);
					//perform erode and dilate to fill the gap
					erode(frame.binary, frame.binary, getStructuringElement(MORPH_ERODE, Size(12, 12)));
					dilate(frame.binary, frame.binary, getStructuringElement(MORPH_DILATE, Size(9, 9)));
					TrafficOfficer::pushDetectingQueue(frame);
				}
			}
		}
	};
}