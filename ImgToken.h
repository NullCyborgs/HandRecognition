#pragma once
#include<opencv2\opencv.hpp>
#include<vector>
namespace HandRecognition{
	class ImgToken{
	public:
		//the original img from the cam
		cv::Mat original;
		//the binary img from the processor
		cv::Mat binary;
		//the contour img from the detector
		cv::Mat contour;
		//contours that have been extracted from the img
		std::vector<std::vector<cv::Point> > contours;
		//herifuck
		std::vector<cv::Vec4i> h;
		//index of the biggest contour
		int biggestContourIX;
		//convex hull points of the biggest contour
		std::vector<cv::Point> hullP;
		//convex hull indices of the biggeest contour
		std::vector<int> hullI;
		//defects of the biggest contour
		std::vector<cv::Vec4i> defects;
		//finger tips of the hand
		std::vector<cv::Point> fingerTips;
		//bounding rectangle of the hand
		cv::Rect rect;
		
	};
}