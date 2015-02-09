#include"HandDetector.h"
#include"TrafficOfficer.h"
#include"WindowManager.h"
#include<vector>
#include<math.h>
#include<sstream>
using namespace std;
using namespace HandRecognition;
using namespace cv;
#define PI 3.14159
string intToString(int number){
	stringstream ss;
	ss << number;
	string str = ss.str();
	return str;
}
int HandDetector::getBiggestContour(ImgToken frame){
	int biggestContourIX = -1;
	double maxi = 0;
	for (int i = 0; i < frame.contours.size(); i++)
	{
		auto ar = contourArea(frame.contours[i]);
		if (ar>maxi){
			maxi = ar;
			biggestContourIX = i;
		}
	}
	return biggestContourIX;
}
float HandDetector::distance(Point a, Point b){
	float d = sqrt(fabs(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2)));
	return d;
}
float HandDetector::getAngle(Point s, Point f, Point e){
	float l1 = distance(f, s);
	float l2 = distance(f, e);
	float dot = (s.x - f.x)*(e.x - f.x) + (s.y - f.y)*(e.y - f.y);
	float angle = acos(dot / (l1*l2));
	angle = angle * 180 / PI;
	return angle;
}
void HandDetector::removeRepeatedEndPoints(std::vector<cv::Vec4i> defects,ImgToken& img){
	Vec4i temp;
	float avgX, avgY;
	float tolerance = img.rect.width / 6;
	int startidx, endidx, faridx;
	int startidx2, endidx2;
	for (int i = 0; i<defects.size(); i++){
		for (int j = i; j<defects.size(); j++){
			startidx = defects[i][0]; Point ptStart(img.contours[img.biggestContourIX][startidx]);
			endidx = defects[i][1]; Point ptEnd(img.contours[img.biggestContourIX][endidx]);
			startidx2 = defects[j][0]; Point ptStart2(img.contours[img.biggestContourIX][startidx2]);
			endidx2 = defects[j][1]; Point ptEnd2(img.contours[img.biggestContourIX][endidx2]);
			if (distance(ptStart, ptEnd2) < tolerance){
				img.contours[img.biggestContourIX][startidx] = ptEnd2;
				break;
			}if (distance(ptEnd, ptStart2) < tolerance){
				img.contours[img.biggestContourIX][startidx2] = ptEnd;
			}
		}
	}
}
void HandDetector::eleminateDefects(ImgToken& frame){
	int tolerance = frame.rect.height / 5;
	float angularTolerance = 95;
	vector<Vec4i> newDefects;
	int startIX, endIX, farIX;
	auto d = frame.defects.begin();
	while (d != frame.defects.end()){
		Vec4i& v = *d;
		startIX = v[0];
		Point startPt(frame.contours[frame.biggestContourIX][startIX]);
		endIX = v[1];
		Point endPt(frame.contours[frame.biggestContourIX][endIX]);
		farIX = v[2];
		Point farPt(frame.contours[frame.biggestContourIX][farIX]);

		if (distance(startPt, farPt) > tolerance &&
			distance(endPt, farPt) > tolerance &&
			getAngle(startPt, farPt, endPt) < angularTolerance){
		}
		else if (startPt.y>(frame.rect.y + frame.rect.height - frame.rect.height / 4)){

		}
		else{
			newDefects.push_back(v);
		}
		d++;
	}
	frame.defects.clear();
	frame.defects = newDefects;
	removeRepeatedEndPoints(frame.defects, frame);
}
void HandDetector::checkHand(ImgToken& frame){
	isHand = true;
	if (frame.fingerTips.size() > 5)
		isHand = false;
	else if (frame.rect.height == 0 || frame.rect.width == 0)
		isHand = false;
	else if (frame.rect.height / frame.rect.width > 4 ||
		frame.rect.width / frame.rect.height > 4)
		isHand = false;
	else if (frame.rect.x < 20)
		isHand = false;	
}
void HandDetector::getFingerTips(ImgToken& frame){
	float area = contourArea(frame.contours[frame.biggestContourIX]) / 2000;
	cout << area << endl;
	frame.fingerTips.clear();
	int i = 0;
	auto d = frame.defects.begin();
	while (d != frame.defects.end()){
		Vec4i& v = *d;
		int startIX = v[0];
		Point startPt = frame.contours[frame.biggestContourIX][startIX];
		int endIX = v[1];
		Point endPt = frame.contours[frame.biggestContourIX][endIX];
		int farIX = v[2];
		Point farPt = frame.contours[frame.biggestContourIX][farIX];
		float depth = v[3] / 256;

		if (depth >= 20 && depth <= 200){
			line(frame.original, startPt, farPt, CV_RGB(0, 255, 0), 2);
			line(frame.original, endPt, farPt, CV_RGB(0, 255, 0), 2);
			circle(frame.original, startPt, 4, Scalar(0, 255, 0), 4);
			frame.fingerTips.push_back(startPt);
		}
		d++;
	}

}
void HandDetector::print(cv::Mat& img, std::string txt,Point p, Scalar c){
	int fontFace = FONT_HERSHEY_PLAIN;
	putText(img, txt, p, fontFace, 1.2f, c, 2);
}
std::vector<cv::Point> HandDetector::eleminateClosePoints(std::vector<cv::Point> frame, float tolerance){
	vector<Point> newFingers;
	vector<bool> taken(frame.size());
	vector<bool> inserted(frame.size());
	for (int i = 0; i < frame.size(); i++){
		if (taken[i])
			continue;
		taken[i] = true;
		for (int j = i; j < frame.size(); j++){
			if (taken[j])
				continue;
			if (distance(frame[i], frame[j]) < tolerance){
				if (!inserted[i] && !inserted[j]){
					newFingers.push_back(frame[i]);
					inserted[i] = true;
					inserted[j] = true;
				}
				taken[j] = true;
				//i++;
			}
		}
	}
	return newFingers;
}
int Process(ImgToken& frame, vector<Point>& ft){
	int koko = 0;
	for (int i = 1; i < frame.contours[frame.biggestContourIX].size()-1; i++){
		Point prev = frame.contours[frame.biggestContourIX][i - 1];
		Point cur = frame.contours[frame.biggestContourIX][i];
		Point next = frame.contours[frame.biggestContourIX][i + 1];
		if (cur.y<=prev.y && cur.y <= next.y){
			//circle(frame.original, cur, 3, Scalar(0, 0, 255), 3);
			ft.push_back(cur);
			koko++;
		}
	}
	return koko;
}
void HandDetector::detect(){
	ImgToken frame;
	while (true){
		bool gotIt = false;

		//peeking the queue
		if (TrafficOfficer::peekDetectingQueue()){
			//getting the frame
			frame = TrafficOfficer::popDetectingQueue();
			gotIt = true;
		}
		if (gotIt){
			//processing the frame
			frame.contour = frame.binary.clone();
			//retreving the contours
			
			findContours(frame.contour, frame.contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
			//getting the biggest contour
			frame.biggestContourIX = getBiggestContour(frame);
			//getting bounding rectangle of the biggest contour and drawing it to the original img
			frame.rect = boundingRect(frame.contours[frame.biggestContourIX]);
			rectangle(frame.original, frame.rect, Scalar(255, 0, 0),3);

			convexHull(Mat(frame.contours[frame.biggestContourIX]), frame.hullP,false, true);
			convexHull(Mat(frame.contours[frame.biggestContourIX]), frame.hullI, false, false);
			approxPolyDP(Mat(frame.hullP), frame.hullP, 3, true);

			//drawing the conves hull shape
			for (int i = 0; i < frame.hullP.size(); i++){
				circle(frame.original, frame.hullP[i], 4, Scalar(0, 0, 255), 4);
				if (i<frame.hullP.size()-1)
					line(frame.original, frame.hullP[i], frame.hullP[i + 1], Scalar(0, 0, 255), 3);
				else
					line(frame.original, frame.hullP[i], frame.hullP[0], Scalar(0, 0, 255), 3);
			}

			convexityDefects(frame.contours[frame.biggestContourIX], frame.hullI, frame.defects);
			//eleminateDefects(frame);
			getFingerTips(frame);
			//frame.fingerTips = eleminateClosePoints(frame.fingerTips, 50);
			//checkHand(frame);
			int nFingers2 = 0;
			for (int i = 0; i < frame.fingerTips.size(); i++){
				if (frame.fingerTips[i].y <= frame.rect.y+frame.rect.height*(0.40)){
					//circle(frame.original, frame.fingerTips[i], 3, Scalar(255, 0, 0), 3);
					nFingers2++;
				}
				print(frame.original, intToString(i), frame.fingerTips[i], Scalar(255, 255, 255));
			}

			print(frame.original, "Fingers Raised:", Point(10, 15), Scalar(255, 255, 255));
			print(frame.original, intToString(min(5,nFingers2)), Point(10, 40), Scalar(255, 255, 255));



			pyrDown(frame.binary, frame.binary);
			pyrDown(frame.binary, frame.binary);
			Rect roi(Point(3 * frame.contour.cols / 4, 0), frame.binary.size());
			frame.binary.copyTo(frame.contour(roi));

			TrafficOfficer::pushViewQueue(frame);

		}
	}
}