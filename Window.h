#pragma once
#include<string>
namespace HandRecognition{
	class Window{
	private:
		//string to hold window id
		std::string _id;
		//window deminsions
		unsigned int _width, _height;

		//init function to init a window
		void init();
		//resize function to resize a window
		void resize();
	public:
		//constructor
		Window(std::string, unsigned int width = 800, unsigned int height = 600);

		//destructor
		~Window();

		//getters & setters
		unsigned int getWidth();
		unsigned int getHeight();
		std::string getID();

		void setWidth(unsigned int val);
		void setHeight(unsigned int val);
	};
}