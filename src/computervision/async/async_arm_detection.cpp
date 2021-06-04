#include <iostream>
#include "async_arm_detection.h"
#include "../OpenPoseVideo.h"
#include <thread>
#include "StaticCameraInstance.h"


namespace computervision
{
	AsyncArmDetection::AsyncArmDetection()
	{

	}

	void AsyncArmDetection::run_arm_detection(std::function<void(std::vector<Point>, cv::Mat poinst_on_image)> points_ready_func, OpenPoseVideo op)
	{
		VideoCapture cap = static_camera::getCap();
		
		std::cout << "STARTING THREAD LAMBDA" << std::endl;
		/*cv::VideoCapture cap = static_camera::GetCap();*/

		if (!cap.isOpened())
		{
			std::cout << "capture was closed, opening..." << std::endl;
			cap.open(0);
		}

		while (true)
		{
			Mat img;
			cap.read(img);
			op.movementSkeleton(img, points_ready_func);
		}
	}

	void AsyncArmDetection::start(std::function<void(std::vector<Point>, cv::Mat poinst_on_image)> points_ready_func, OpenPoseVideo op)
	{

		std::cout << "starting function" << std::endl;


		std::thread async_arm_detect_thread(&AsyncArmDetection::run_arm_detection,this, points_ready_func, op);

		async_arm_detect_thread.detach(); // makes sure the thread is detached from the variable.
	}
}
