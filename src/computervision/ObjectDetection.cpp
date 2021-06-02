
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "ObjectDetection.h"
#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FaceDetector.h"
#include "FingerCount.h"
#include "async/StaticCameraInstance.h"

namespace computervision
{

	cv::Mat img, imgGray, img2, img2Gray, img3, img4;

	int handMaskStartXPos, handMaskStartYPos, handMaskWidth, handMaskHeight;
	bool handMaskGenerated = false;

	Mat frame, frameOut, handMask, foreground, fingerCountDebug;
	BackgroundRemover backgroundRemover;
	SkinDetector skinDetector;
	FaceDetector faceDetector;
	FingerCount fingerCount;

	cv::VideoCapture cap = computervision_async::getCap();

	ObjectDetection::ObjectDetection()
	{
	}

	cv::Mat ObjectDetection::readCamera() {
		cap.read(img);
		return img;
	}

	cv::VideoCapture ObjectDetection::getCap()
	{
		return cap;
	}

	bool ObjectDetection::detectHand(Mat cameraFrame)
	{
		Mat inputFrame = generateHandMaskSquare(cameraFrame);
		frameOut = inputFrame.clone();

		// detect skin color
		skinDetector.drawSkinColorSampler(frameOut);

		// remove background from image
		foreground = backgroundRemover.getForeground(inputFrame);

		// detect the hand contours
		handMask = skinDetector.getSkinMask(foreground);

		// count the amount of fingers and put the info on the matrix
		fingerCountDebug = fingerCount.findFingersCount(handMask, frameOut);

		// get the amount of fingers
		int fingers_amount = fingerCount.getAmountOfFingers();

		// draw the hand rectangle on the camera input, and draw text showing if the hand is open or closed.
		drawHandMaskRect(&cameraFrame);
		string hand_text = fingers_amount > 0 ? "open" : "closed";
		putText(cameraFrame,hand_text, Point(10, 75), FONT_HERSHEY_PLAIN, 2.0, Scalar(255, 0, 255),3);
		imshow("camera", cameraFrame);

		imshow("output", frameOut);
		imshow("foreground", foreground);
		imshow("handMask", handMask);
		imshow("handDetection", fingerCountDebug);

		int key = waitKey(1);

		if (key == 98) // b, calibrate the background
			backgroundRemover.calibrate(inputFrame);
		else if (key == 115) // s, calibrate the skin color
			skinDetector.calibrate(inputFrame);

		return fingers_amount > 0;
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

	void ObjectDetection::showWebcam()
	{
		imshow("Webcam image", img);
	}


}