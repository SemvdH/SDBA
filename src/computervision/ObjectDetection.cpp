#include "ObjectDetection.h"
#include "ObjectDetection.h"
//#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FaceDetector.h"
#include "FingerCount.h"

namespace computervision
{
	cv::VideoCapture cap(0);
	cv::Mat img, imgGray, img2, img2Gray, img3, img4;

	Mat frame, frameOut, handMask, foreground, fingerCountDebug;
	//BackgroundRemover backgroundRemover;
	SkinDetector skinDetector;
	FaceDetector faceDetector;
	FingerCount fingerCount;


	ObjectDetection::ObjectDetection()
	{
	}

	void ObjectDetection::Init() 
	{
		cap.read(frame);
		skinDetector.drawSkinColorSampler(frameOut);

		foreground = backgroundRemover.getForeground(frame);

		faceDetector.removeFaces(frame, foreground);
		handMask = skinDetector.getSkinMask(foreground);
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