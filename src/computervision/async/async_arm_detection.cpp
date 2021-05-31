#include <iostream>
#include "async_arm_detection.h"
#include "../OpenPoseVideo.h"
#include <thread>
#include "../VideoCapture.h"


namespace computervision
{
	AsyncArmDetection::AsyncArmDetection()
	{

	}

	void AsyncArmDetection::run_arm_detection()
	{

	}

	void AsyncArmDetection::start(std::function<void(std::vector<Point>)> points_ready_func, OpenPoseVideo op)
	{

		auto lambda = [](std::function<void(std::vector<Point>)> f, OpenPoseVideo op) {
			std::cout << "STARTING THREAD LAMBDA" << std::endl;

			videocapture::getMutex()->lock();
			if (!videocapture::getCap().isOpened())
			{
				std::cout << "error opening video" << std::endl;
				videocapture::getCap().open(1);
				return;
			}
			videocapture::getMutex()->unlock();
			Mat img;
			while (true)
			{
				videocapture::getMutex()->lock();

				videocapture::getCap().read(img);
				imshow("image", img);

				videocapture::getMutex()->unlock();
				op.movementSkeleton(img, f);
			}
		};

		std::cout << "starting function" << std::endl;
		std::thread async_arm_detect_thread(lambda, points_ready_func, op);
	}
}
