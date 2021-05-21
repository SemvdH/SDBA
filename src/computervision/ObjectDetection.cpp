#include "ObjectDetection.h"
namespace computervision
{
	cv::VideoCapture cap(0);
	cv::Mat img, imgGray, img2, img2Gray, img3, img4;

	ObjectDetection::ObjectDetection()
	{
	}

	void ObjectDetection::readWebcam()
	{
		cap.read(img);
	}

	void ObjectDetection::calculateDifference()
	{
		cap.read(img);
		cap.read(img2);

		cv::cvtColor(img, imgGray, cv::COLOR_RGBA2GRAY);
		cv::cvtColor(img2, img2Gray, cv::COLOR_RGBA2GRAY);

		cv::absdiff(imgGray, img2Gray, img3);
		cv::threshold(img3, img4, 50, 170, cv::THRESH_BINARY);

		imshow("threshold", img4);
	}

	void ObjectDetection::showWebcam()
	{
		imshow("Webcam image", img);
	}


}