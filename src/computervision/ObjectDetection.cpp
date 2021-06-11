
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "ObjectDetection.h"
#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FingerCount.h"
#include "async/StaticCameraInstance.h"
#include "calibration/HandCalibrator.h"

namespace computervision
{

	cv::Mat img, img_gray, img2, img2_gray, img3, img4;

	int hand_mask_start_x_pos, hand_mask_start_y_pos, hand_mask_width, hand_mask_height;
	bool hand_mask_generated = false;

	Mat frame, frame_out, handMask, foreground, fingerCountDebug;
	BackgroundRemover background_remover;
	SkinDetector skin_detector;
	FingerCount finger_count;
	handcalibration::HandCalibrator hand_calibrator;

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
		skin_detector.drawSkinColorSampler(camera_frame);

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
		

		hand_calibrator.SetAmountOfFingers(fingers_amount);
		finger_count.DrawHandContours(camera_frame);
		hand_calibrator.DrawHandCalibrationText(camera_frame);
		imshow("camera", camera_frame);



		/*imshow("output", frame_out);
		imshow("foreground", foreground);
		imshow("handMask", handMask);
		imshow("handDetection", fingerCountDebug);*/

		hand_present = hand_calibrator.CheckIfHandPresent(handMask,handcalibration::HandDetectionType::MENU);
		hand_calibrator.SetHandPresent(hand_present);



		int key = waitKey(1);

		if (key == 98) // b, calibrate the background
		{
			background_remover.calibrate(input_frame);
			hand_calibrator.SetBackGroundCalibrated(true);
		}
		else if (key == 115) // s, calibrate the skin color
		{
			skin_detector.calibrate(input_frame);
			hand_calibrator.SetSkinCalibration(true);

		}


		return fingers_amount > 0;
	}

	void ObjectDetection::CalculateDifference()
	{
		cap.read(img);
		cap.read(img2);

		cv::cvtColor(img, img_gray, cv::COLOR_RGBA2GRAY);
		cv::cvtColor(img2, img2_gray, cv::COLOR_RGBA2GRAY);

		cv::absdiff(img_gray, img2_gray, img3);
		cv::threshold(img3, img4, 50, 170, cv::THRESH_BINARY);

		imshow("threshold", img4);
	}


	cv::Mat ObjectDetection::GenerateHandMaskSquare(cv::Mat img)
	{
		hand_mask_start_x_pos = 20;
		hand_mask_start_y_pos = img.rows / 5;
		hand_mask_width = img.cols / 3;
		hand_mask_height = img.cols / 3;


		cv::Mat mask = cv::Mat::zeros(img.size(), img.type());
		cv::Mat distance_img = cv::Mat::zeros(img.size(), img.type());

		cv::rectangle(mask, Rect(hand_mask_start_x_pos, hand_mask_start_y_pos, hand_mask_width, hand_mask_height), Scalar(255, 255, 255), -1);

		img.copyTo(distance_img, mask);

		hand_mask_generated = true;
		return distance_img;

	}

	bool ObjectDetection::DrawHandMask(cv::Mat* input)
	{
		if (!hand_mask_generated) return false;
		rectangle(*input, Rect(hand_mask_start_x_pos, hand_mask_start_y_pos, hand_mask_width, hand_mask_height), Scalar(255, 255, 255));
		return true;
	}

	void ObjectDetection::ShowWebcam()
	{
		imshow("Webcam image", img);
	}


}