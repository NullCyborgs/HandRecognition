#pragma once
#include<queue>
#include<opencv2\opencv.hpp>
#include<atomic>
#include<memory>
#include<map>
#include"ImgToken.h"
namespace HandRecognition{
	class TrafficOfficer{
	private:
		//queue that will contain the frames that's need procssing by the image processor
		static std::queue<ImgToken> _processingQueue;
		//queue that will conatain the frames that's need to be go through the detector
		static std::queue<ImgToken> _detectingQueue;
		//queue for the viewing window
		static std::queue<ImgToken> _viewQueue;
		//Map for storing global values
		static std::map<std::string, float> _valMap;

	public:
		//two functions to check if there exists a frames in the queues
		static bool peekProcessingQueue();
		static bool peekDetectingQueue();
		static bool peekViewQueue();

		//two functions to get the top of the queue
		static ImgToken popProcessingQueue();
		static ImgToken popDetectingQueue();
		static ImgToken popViewQueue();

		//two functions to push to the queues
		static void pushProcessingQueue(ImgToken);
		static void pushDetectingQueue(ImgToken);
		static void pushViewQueue(ImgToken);

		static void val(std::string key, float val);
		static float val(std::string key);

		static void cleanUp();
	};
}