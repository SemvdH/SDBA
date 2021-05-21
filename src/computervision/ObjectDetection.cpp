#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "ObjectDetection.h"
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

	bool ObjectDetection::Init() 
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

		return true;
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