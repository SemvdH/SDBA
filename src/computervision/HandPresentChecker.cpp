#include "HandPresentChecker.h"
#include <opencv2/imgproc.hpp>
#include <iostream>


namespace computervision
{
	bool check_if_hand_present(cv::Mat inputImage)
	{
		std::vector<std::vector<cv::Point>> points;
		cv::Mat imgCont;
		cv::findContours(inputImage, points, cv::RetrievalModes::RETR_LIST, cv::ContourApproximationModes::CHAIN_APPROX_SIMPLE);
		bool hand_present = points.size() > 0;
		std::cout << (hand_present ? "hey a hand!" : "damn no hand") << std::endl;
		return hand_present;
	}

}
