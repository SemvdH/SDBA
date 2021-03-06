
#include "object_detection.h"

#define TIME_DURATION 1.0f

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
	float time = 0;
	int seconds_left = 5; // calibration countdown

	bool background_calibrated = false;
	bool skin_calibrated = false;
	bool hand_open = false;

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
		//calculate deltatime
		if (!background_calibrated || !skin_calibrated)
		{
			UpdateTime();

			if (time >= TIME_DURATION)
			{
				std::cout << "timer finised,  seconds left: " << seconds_left << std::endl;
				seconds_left--;
				time = 0;
			}
		}


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

		if (seconds_left <= 0)
		{
			if (!background_calibrated)
			{
				background_remover.calibrate(input_frame);
				background_calibrated = true;
				hand_calibrator.SetBackGroundCalibrated(background_calibrated);
				seconds_left = 5;
				time = 0;
			}
			else
			{

				if (!skin_calibrated)
				{
					skin_detector.calibrate(input_frame);
					skin_calibrated = true;
					hand_calibrator.SetSkinCalibration(skin_calibrated);
					time = 0;
					calibration_callback();
				}
			}

		}

		hand_calibrator.SetAmountOfFingers(fingers_amount);
		finger_count.DrawHandContours(camera_frame);
		hand_calibrator.DrawHandCalibrationText(camera_frame);

		std::string calibration_text = (!background_calibrated ? "calibrating background in " : (!skin_calibrated ? "calibrating skin in " : ""));
		calibration_text += std::to_string(seconds_left);
		if (!background_calibrated || !skin_calibrated)
		{
			cv::rectangle(camera_frame, cv::Rect(0, camera_frame.rows - 120, 500, 50), cv::Scalar(0, 0, 0), -1);
			cv::putText(camera_frame, calibration_text, cv::Point(5, camera_frame.rows-80), cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(255, 0, 255), 2);
		}

		if (background_calibrated && !skin_calibrated)
		{
			cv::putText(camera_frame, "put your hand in the square", cv::Point(5, camera_frame.rows - 100), cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(255, 0, 255), 2);
		}
		imshow("camera", camera_frame);

		// uncomment these lines to show debug hand information
		/*imshow("output", frame_out);
		imshow("foreground", foreground);
		imshow("handMask", handMask);
		imshow("handDetection", fingerCountDebug);*/

		hand_present = hand_calibrator.CheckIfHandPresent(handMask, handcalibration::HandDetectionType::MENU);
		hand_calibrator.SetHandPresent(hand_present);

		hand_open = fingers_amount > 0;
		return hand_open;
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

	void ObjectDetection::UpdateTime()
	{
		double current_time = glfwGetTime();
		static double last_frame_time = current_time;
		double delt_time = current_time - last_frame_time;
		last_frame_time = current_time;

		time += delt_time;
	}

	bool ObjectDetection::IsHandOpen()
	{
		return hand_open;
	}

	bool ObjectDetection::IsCalibrated()
	{
		return background_calibrated && skin_calibrated;
	}


}