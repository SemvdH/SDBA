
#include "ObjectDetection.h"
#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FaceDetector.h"
#include "FingerCount.h"

namespace computervision
{
	cv::VideoCapture cap(0);

	cv::Mat img, imgGray, img2, img2Gray, img3, img4;

	Mat frame, frameOut, handMask, foreground, fingerCountDebug;
	BackgroundRemover backgroundRemover;
	SkinDetector skinDetector;
	FaceDetector faceDetector;
	FingerCount fingerCount;


	ObjectDetection::ObjectDetection()
	{
	}

	bool ObjectDetection::setup() 
	{
		if (!cap.isOpened()) {
			cout << "Can't find camera!" << endl;
			return false;
		}

		cap.read(frame);
		frameOut = frame.clone();

		skinDetector.drawSkinColorSampler(frameOut);

		foreground = backgroundRemover.getForeground(frame);

		faceDetector.removeFaces(frame, foreground);
		handMask = skinDetector.getSkinMask(foreground);
		fingerCountDebug = fingerCount.findFingersCount(handMask, frameOut);

		//backgroundRemover.calibrate(frame);


		imshow("output", frameOut);
		imshow("foreground", foreground);
		imshow("handMask", handMask);
		imshow("handDetection", fingerCountDebug);

		int key = waitKey(1);

		if (key == 98) // b
			backgroundRemover.calibrate(frame);
		else if (key == 115) // s
			skinDetector.calibrate(frame);

		return true;
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

	void ObjectDetection::detect()
	{
		int key = waitKey(1);
			
		if (key == 98) // b
			backgroundRemover.calibrate(frame);
		else if (key == 115) // s
			skinDetector.calibrate(frame);
	}

	void ObjectDetection::showWebcam()
	{
		imshow("Webcam image", img);
	}


}