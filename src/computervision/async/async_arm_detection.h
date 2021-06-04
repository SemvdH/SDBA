#pragma once
#include <vector>
#include <opencv2/core/types.hpp>
#include <opencv2/videoio.hpp>
#include <functional>
#include "../OpenPoseVideo.h"
#include "StaticCameraInstance.h"


namespace computervision
{
	class AsyncArmDetection
	{
	public:
		AsyncArmDetection(void);

		
		void start(std::function<void(std::vector<cv::Point>, cv::Mat poinst_on_image)>, computervision::OpenPoseVideo op);
	private:
		void run_arm_detection(std::function<void(std::vector<Point>, cv::Mat poinst_on_image)> points_ready_func, OpenPoseVideo op);
	};

}
