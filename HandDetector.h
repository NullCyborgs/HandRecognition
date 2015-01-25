#pragma once
#include<iostream>
namespace HandRecognition{
	class HandDetector{
	public:
		void detect(){
			while (true){
				MatPtr frame;
				bool gotIt = false;
				std::cout << "detecting" << std::endl;
				if (TrafficOfficer::peekDetectingQueue()){
					frame = TrafficOfficer::popDetectingQueue();
					gotIt = true;
				}
				if (gotIt){
					TrafficOfficer::pushViewQueue(frame);
				}
			}
		}
	};
}