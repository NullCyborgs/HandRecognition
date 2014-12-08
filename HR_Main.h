#pragma once
#include <thread>
#include <vector>

namespace HandRecognition{
	class HR_Main{
	private:
		//Frame's width and height read by camera
		int _cameraWidth, _cameraHeight;
		//Vector that stores the threads
		std::thread _processorThread, _detectorThread;
	public:
		HR_Main();
		~HR_Main();

		//Launch camera
		void Main();
		//Launch threads
		void launchThreads();
	};
}