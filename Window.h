#pragma once
#include<string>
#include<opencv2\highgui\highgui.hpp>
#include<memory>
namespace HandRecognition{
	class Window{
	private:
		//string to hold window id
		std::string _id;
		//window deminsions
		unsigned int _width, _height;
		//input array that's being displayed by this window
		cv::Mat _frame;

		//init boolean
		bool initIn;

		//init function to init a window
		void init();
		//resize function to resize a window
		void resize();
	public:
		//constructor
		Window(std::string, unsigned int width = 800, unsigned int height = 600);

		Window();
		//destructor
		~Window();
		//update function to be called so that the window will be shown
		void update();
		//show function for updating the current frame
		void show(cv::Mat frame);

		//getters & setters
		unsigned int getWidth();
		unsigned int getHeight();
		std::string getID();

		bool isInit();

		void setWidth(unsigned int val);
		void setHeight(unsigned int val);
	};
	typedef std::shared_ptr<Window> WindowPtr;
}