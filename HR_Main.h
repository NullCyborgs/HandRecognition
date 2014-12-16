#pragma once
#include <thread>
#include <vector>
#include "FrameProcessor.h"
#include "HandDetector.h"

namespace HandRecognition{
	class HR_Main{
	private:
		//Frame's width and height read by camera
		int _cameraWidth, _cameraHeight;
		//Vector that stores the threads
		std::thread* _processorThread,* _detectorThread;
		//two main classes one that process the image and other that detect it
		FrameProcessor* _frameProcessor;
		HandDetector* _handDetector;
	public:
		HR_Main();
		~HR_Main();

		//Launch camera
		void Main();
		//Launch threads
		void launchThreads();
	};
}