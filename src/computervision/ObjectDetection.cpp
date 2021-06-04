
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "ObjectDetection.h"
#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FaceDetector.h"
#include "FingerCount.h"
#include "async/StaticCameraInstance.h"
#include "HandPresentChecker.h"

namespace computervision
{

	cv::Mat img, imgGray, img2, img2Gray, img3, img4;

	int handMaskStartXPos, handMaskStartYPos, handMaskWidth, handMaskHeight;
	bool handMaskGenerated = false;

	Mat frame, frame_out, handMask, foreground, fingerCountDebug;
	BackgroundRemover background_remover;
	SkinDetector skin_detector;
	FingerCount finger_count;

	cv::VideoCapture cap = static_camera::getCap();

	ObjectDetection::ObjectDetection()
	{
	}

	cv::Mat ObjectDetection::ReadCamera() {
		cap.read(img);
		return img;
	}

	cv::VideoCapture ObjectDetection::GetCap()
	{
		return cap;
	}

	bool ObjectDetection::DetectHand(Mat camera_frame, bool& hand_present)
	{
		Mat input_frame = GenerateHandMaskSquare(camera_frame);
		frame_out = input_frame.clone();

		// detect skin color
		skin_detector.drawSkinColorSampler(frame_out);

		// remove background from image
		foreground = background_remover.getForeground(input_frame);

		// detect the hand contours
		handMask = skin_detector.getSkinMask(foreground);

		// count the amount of fingers and put the info on the matrix
		fingerCountDebug = finger_count.findFingersCount(handMask, frame_out);

		// get the amount of fingers
		int fingers_amount = finger_count.getAmountOfFingers();

		// draw the hand rectangle on the camera input, and draw text showing if the hand is open or closed.
		DrawHandMask(&camera_frame);
		string hand_text = fingers_amount > 0 ? "open" : "closed";
		putText(camera_frame,hand_text, Point(10, 75), FONT_HERSHEY_PLAIN, 2.0, Scalar(255, 0, 255),3);
		imshow("camera", camera_frame);

		//imshow("output", frame_out);
		//imshow("foreground", foreground);
		//imshow("handMask", handMask);
		//imshow("handDetection", fingerCountDebug);

		hand_present = CheckIfHandPresent(handMask);



		int key = waitKey(1);

		if (key == 98) // b, calibrate the background
			background_remover.calibrate(input_frame);
		else if (key == 115) // s, calibrate the skin color
			skin_detector.calibrate(input_frame);

		return fingers_amount > 0;
	}

	void ObjectDetection::CalculateDifference()
	{
		cap.read(img);
		cap.read(img2);

		cv::cvtColor(img, imgGray, cv::COLOR_RGBA2GRAY);
		cv::cvtColor(img2, img2Gray, cv::COLOR_RGBA2GRAY);

		cv::absdiff(imgGray, img2Gray, img3);
		cv::threshold(img3, img4, 50, 170, cv::THRESH_BINARY);

		imshow("threshold", img4);
	}


	cv::Mat ObjectDetection::GenerateHandMaskSquare(cv::Mat img)
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

	bool ObjectDetection::DrawHandMask(cv::Mat* input)
	{
		if (!handMaskGenerated) return false;
		rectangle(*input, Rect(handMaskStartXPos, handMaskStartYPos, handMaskWidth, handMaskHeight), Scalar(255, 255, 255));
		return true;
	}

	void ObjectDetection::ShowWebcam()
	{
		imshow("Webcam image", img);
	}


}