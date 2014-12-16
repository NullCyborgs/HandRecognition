#pragma once
#include<queue>
#include<opencv2\opencv.hpp>
#include<atomic>
#include"AtomicWrapper.h"
namespace HandRecognition{
	//this class is used to manage the queue of frames that will go through the pipeline of the application
	class TrafficOfficer{
	private:
		//queue that will contain the frames that's need procssing by the image processor
		static std::queue<cv::Mat > _processingQueue;
		//queue that will conatain the frames that's need to be go through the detector
		static std::queue<cv::Mat > _detectingQueue;

	public:
		//two functions to check if there exists a frames in the queues
		static bool peekProcessingQueue();
		static bool peekDetectingQueue();

		//two functions to get the top of the queue
		static cv::Mat popProcessingQueue();
		static cv::Mat popDetectingQueue();

		//two functions to push to the queues
		static void pushProcessingQueue(cv::Mat& frame);
		static void pushDetectingQueue(cv::Mat& frame);

		static void cleanUp();
	};
}