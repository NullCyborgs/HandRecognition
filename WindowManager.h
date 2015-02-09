#pragma once
#include"Window.h"
#include<map>
#include<string>
#include<opencv2\highgui\highgui.hpp>
namespace HandRecognition{
	class WindowManager{
	private:
		//map that will contain everywindow
		static std::map<std::string, WindowPtr> _windowMap;
		//main window that everything will be shown in it by defualt
		static WindowPtr _mainWindow;

	public:
		//to show img in a window, the default is the main window
		static bool show(cv::Mat frame, std::string id = "");
		//function to remove a window from map
		static void removeWindow(std::string id);
		//function to add window to the map, and if it's the main window the boolean is checked
		static void addWindow(WindowPtr win, bool main = false);
		//function to update all the windows
		static void update();
		//cleanUp function to empty the class for destruction
		static void cleanUp();
	};
}