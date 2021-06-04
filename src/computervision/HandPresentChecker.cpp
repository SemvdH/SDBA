#include "HandPresentChecker.h"
#include <opencv2/imgproc.hpp>
#include <iostream>

#define MIN_HAND_SIZE 10000

namespace computervision
{
	bool check_if_hand_present(cv::Mat inputImage)
	{
		std::vector<std::vector<cv::Point>> points;
		cv::Mat imgCont;
		cv::findContours(inputImage, points, cv::RetrievalModes::RETR_LIST, cv::ContourApproximationModes::CHAIN_APPROX_SIMPLE);

		if (points.size() == 0) return false;

		for (int p = 0; p < points.size(); p++)
		{
			int area = cv::contourArea(points[p]);
			if (area > MIN_HAND_SIZE) return true;
		}
		
		return false;
	}

}
