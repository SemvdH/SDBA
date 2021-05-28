#pragma once
#include <vector>
#include <opencv2/core/types.hpp>
#include <opencv2/videoio.hpp>
#include <functional>
#include "../OpenPoseVideo.h"


namespace computervision
{
	class AsyncArmDetection
	{
	public:
		AsyncArmDetection(void);

		
		void start(std::function<void(std::vector<cv::Point>)>, cv::VideoCapture cap, computervision::OpenPoseVideo op);
	private:
		void run_arm_detection();
	};

}
