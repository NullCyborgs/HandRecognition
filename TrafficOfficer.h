#pragma once
#include<queue>
#include<opencv2\opencv.hpp>
#include<atomic>
#include<memory>
#include<map>
#include"AtomicWrapper.h"
namespace HandRecognition{
	//this class is used to manage the queue of frames that will go through the pipeline of the application
	typedef std::shared_ptr<cv::Mat> MatPtr;
	class TrafficOfficer{
	private:
		//queue that will contain the frames that's need procssing by the image processor
		static std::queue<MatPtr> _processingQueue;
		//queue that will conatain the frames that's need to be go through the detector
		static std::queue<MatPtr> _detectingQueue;
		//queue for the viewing window
		static std::queue<MatPtr> _viewQueue;
		//Map for storing global values
		static std::map<std::string, float> _valMap;

	public:
		//two functions to check if there exists a frames in the queues
		static bool peekProcessingQueue();
		static bool peekDetectingQueue();
		static bool peekViewQueue();

		//two functions to get the top of the queue
		static MatPtr popProcessingQueue();
		static MatPtr popDetectingQueue();
		static MatPtr popViewQueue();

		//two functions to push to the queues
		static void pushProcessingQueue(MatPtr);
		static void pushDetectingQueue(MatPtr);
		static void pushViewQueue(MatPtr);

		static void val(std::string key, float val);
		static float val(std::string key);

		static void cleanUp();
	};
}