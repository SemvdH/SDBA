#include <iostream>
#include "async_arm_detection.h"
#include "../OpenPoseVideo.h"
#include <thread>


namespace computervision
{
	AsyncArmDetection::AsyncArmDetection()
	{

	}

	void AsyncArmDetection::run_arm_detection()
	{

	}

	void AsyncArmDetection::start(std::function<void(std::vector<Point>)> points_ready_func, cv::VideoCapture cap, OpenPoseVideo op)
	{

		auto lambda = [](std::function<void(std::vector<Point>)> f, cv::VideoCapture c, OpenPoseVideo op) {
			std::cout << "STARTING THREAD LAMBDA" << std::endl;
			cv::VideoCapture cap(0);

			if (!cap.isOpened())
			{
				std::cout << "error opening video" << std::endl;
				return;
			}

			while (true)
			{
				Mat img;
				cap.read(img);
				op.movementSkeleton(img, f);
			}
		};

		std::cout << "starting function" << std::endl;
		std::thread async_arm_detect_thread(lambda, points_ready_func, cap, op);
	}
}
