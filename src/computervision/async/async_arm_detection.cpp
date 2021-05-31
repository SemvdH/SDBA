#include <iostream>
#include "async_arm_detection.h"
#include "../OpenPoseVideo.h"
#include <thread>
#include "../VideoCapture.h"
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


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

		auto lambda = [](cv::Mat img, std::function<void(std::vector<Point>)> f, OpenPoseVideo op, cv::Mat inpBlob) {
			std::cout << "STARTING THREAD LAMBDA" << std::endl;

			//imshow("image", img); 255, Size(368, 368), Scalar(0, 0, 0), false, false);
			op.movementSkeleton(img, inpBlob, f);
			//}
		};

		cv::Mat img = videocapture::readFrame();
		std::cout << "starting function" << std::endl;
		cv::Mat inpBlob = op.getBlobFromImage(videocapture::readFrame());


		std::thread async_arm_detect_thread(lambda, img, points_ready_func, op, inpBlob);
	}
}
