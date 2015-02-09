#pragma once
#include<iostream>
#include<vector>
#include<opencv2\opencv.hpp>
#include<string>
#include"ImgToken.h"
namespace HandRecognition{
	class HandDetector{
	public:
		bool isHand;
		void print(cv::Mat&, std::string,cv::Point,cv::Scalar);
		std::vector<cv::Point> eleminateClosePoints(std::vector<cv::Point>, float tolerance);
		int getBiggestContour(ImgToken);
		float distance(cv::Point, cv::Point);
		float getAngle(cv::Point, cv::Point, cv::Point);
		void removeRepeatedEndPoints(std::vector<cv::Vec4i>,ImgToken&);
		void checkHand(ImgToken&);
		void getFingerTips(ImgToken&);
		void eleminateDefects(ImgToken&);
		void detect();
	};
}