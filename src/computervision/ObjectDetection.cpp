
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "ObjectDetection.h"
#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FaceDetector.h"
#include "FingerCount.h"

namespace computervision
{
	cv::VideoCapture cap(0);

	cv::Mat img, imgGray, img2, img2Gray, img3, img4;

	int handMaskStartXPos, handMaskStartYPos, handMaskWidth, handMaskHeight;
	bool handMaskGenerated = false;

	Mat frame, frameOut, handMask, foreground, fingerCountDebug;
	BackgroundRemover backgroundRemover;
	SkinDetector skinDetector;
	FaceDetector faceDetector;
	FingerCount fingerCount;




	ObjectDetection::ObjectDetection()
	{
	}

	cv::Mat ObjectDetection::readCamera() {
		cap.read(img);
		return img;
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

	bool ObjectDetection::detectHand(Mat inputFrame)
	{
		frameOut = inputFrame.clone();

		skinDetector.drawSkinColorSampler(frameOut);

		foreground = backgroundRemover.getForeground(inputFrame);

		//faceDetector.removeFaces(inputFrame, foreground);
		handMask = skinDetector.getSkinMask(foreground);
		fingerCountDebug = fingerCount.findFingersCount(handMask, frameOut);

		//backgroundRemover.calibrate(frame);


		imshow("output", frameOut);
		imshow("foreground", foreground);
		imshow("handMask", handMask);
		imshow("handDetection", fingerCountDebug);

		int key = waitKey(1);

		if (key == 98) // b
			backgroundRemover.calibrate(inputFrame);
		else if (key == 115) // s
			skinDetector.calibrate(inputFrame);

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


	cv::Mat ObjectDetection::generateHandMaskSquare(cv::Mat img)
	{
		handMaskStartXPos = 20;
		handMaskStartYPos = img.rows / 5;
		handMaskWidth = img.cols / 3;
		handMaskHeight = img.cols / 3;


		cv::Mat mask = cv::Mat::zeros(img.size(), img.type());
		cv::Mat dstImg = cv::Mat::zeros(img.size(), img.type());

		cv::rectangle(mask, Rect(handMaskStartXPos, handMaskStartYPos, handMaskWidth, handMaskHeight), Scalar(255, 255, 255), -1);

		img.copyTo(dstImg, mask);

		handMaskGenerated = true;
		return dstImg;

	}

	bool ObjectDetection::drawHandMaskRect(cv::Mat* input)
	{
		if (!handMaskGenerated) return false;
		rectangle(*input, Rect(handMaskStartXPos, handMaskStartYPos, handMaskWidth, handMaskHeight), Scalar(255, 255, 255));
		return true;
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