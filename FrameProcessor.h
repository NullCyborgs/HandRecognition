#pragma once
#include<iostream>
#include"TrafficOfficer.h"
namespace HandRecognition{
	class FrameProcessor{
	public:
		void process(){
			while (true){
				std::cout << "processing" << std::endl;
				if (TrafficOfficer::peekProcessingQueue())
					TrafficOfficer::popProcessingQueue();
			}
		}
	};
}