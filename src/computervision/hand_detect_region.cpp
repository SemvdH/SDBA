
#include "hand_detect_region.h"
#define TIME_DURATION 1.5f
namespace computervision
{

	HandDetectRegion::HandDetectRegion(std::string id,int x_pos, int y_pos, int width, int height)
	{
		region_id = id;
		start_x_pos = x_pos;
		start_y_pos = y_pos;
		region_width = width;
		region_height = height;
		hand_mask_generated = false;
		hand_present = false;
	}

	void HandDetectRegion::DetectHand(cv::Mat& camera_frame)
	{
		Mat input_frame = GenerateHandMaskSquare(camera_frame);
		frame_out = input_frame.clone();

		if (!background_calibrated || !skin_calibrated)
			if (time >= TIME_DURATION)
			{
				//std::cout << "timer finised,  seconds left: " << seconds_left << std::endl;
				seconds_left--;
				time = 0;
			}
		

		// detect skin color
		skin_detector.drawSkinColorSampler(camera_frame,start_x_pos,start_y_pos,region_width,region_height);

		// remove background from image

		foreground = background_remover.getForeground(input_frame);

		// detect the hand contours
		handMask = skin_detector.getSkinMask(foreground);

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
					if (is_main_skin_detection_region)
						skin_timer_callback();
				}
			}

		}

		// uncomment these lines to show debug hand information
		//imshow("output" + region_id, frame_out);
		//imshow("foreground" + region_id, foreground);
		//imshow("handMask" + region_id, handMask);
		//imshow("handDetection", fingerCountDebug);

		hand_present = hand_calibrator.CheckIfHandPresent(handMask,handcalibration::HandDetectionType::GAME);
		//std::string text = (hand_present ? "hand" : "no");
		//cv::putText(camera_frame, text, cv::Point(start_x_pos, start_y_pos), cv::FONT_HERSHEY_COMPLEX, 2.0, cv::Scalar(0, 255, 255), 2);
		hand_calibrator.SetHandPresent(hand_present);

		//draw black rectangle behind calibration information text
		cv::rectangle(camera_frame, cv::Rect(0, camera_frame.rows - 55, 450, camera_frame.cols), cv::Scalar(0, 0, 0), -1);

		hand_calibrator.DrawBackgroundSkinCalibrated(camera_frame);

		std::string calibration_text = (!background_calibrated ? "calibrating background in " : (!skin_calibrated ? "calibrating skin in " : ""));
		calibration_text += std::to_string(seconds_left);
		if (!background_calibrated || !skin_calibrated)
		{
			cv::rectangle(camera_frame, cv::Rect(0, camera_frame.rows - 130, 600, 60), cv::Scalar(0, 0, 0), -1);
			cv:putText(camera_frame, calibration_text, cv::Point(5, 400), cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(255, 0, 255), 2);
		}
		if (background_calibrated && !skin_calibrated)
		{
			cv::putText(camera_frame, "put your hand in the left square", cv::Point(5, camera_frame.rows - 105), cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(255, 0, 255), 2);
		}

	}

	cv::Mat HandDetectRegion::GenerateHandMaskSquare(cv::Mat img)
	{
		cv::Mat mask = cv::Mat::zeros(img.size(), img.type());
		cv::Mat distance_img = cv::Mat::zeros(img.size(), img.type());

		cv::rectangle(mask, cv::Rect(start_x_pos, start_y_pos, region_width, region_height), cv::Scalar(255, 255, 255), -1);

		img.copyTo(distance_img, mask);

		hand_mask_generated = true;
		return distance_img;
	}

	bool HandDetectRegion::DrawHandMask(cv::Mat* input)
	{
		if (!hand_mask_generated) return false;
		rectangle(*input, Rect(start_x_pos, start_y_pos, region_width, region_height), (hand_present ? Scalar(0, 255, 0) : Scalar(0,0,255)),2);
		return true;
	}

	bool HandDetectRegion::IsHandPresent()
	{
		return hand_present;
	}

	void HandDetectRegion::CalibrateBackground()
	{
		std::cout << "calibrating background " << region_id << std::endl;
		background_remover.calibrate(frame_out);
		hand_calibrator.SetBackGroundCalibrated(true);
	}
	void HandDetectRegion::CalibrateSkin()
	{
		skin_detector.calibrate(frame_out);
		hand_calibrator.SetSkinCalibration(true);
	}

	std::vector<int> HandDetectRegion::CalculateSkinTresholds()
	{
		std::cout << "calibrating skin " << region_id << std::endl;
		hand_calibrator.SetSkinCalibration(true);
		skin_calibrated = true;
		time = 0;
		return skin_detector.calibrateAndReturn(frame_out);
	}

	void HandDetectRegion::setSkinTresholds(std::vector<int>& tresholds)
	{
		std::cout << "setting skin " << region_id << std::endl;
		skin_detector.setTresholds(tresholds);
		hand_calibrator.SetSkinCalibration(true);
		skin_calibrated = true;
		time = 0;
	}

	void HandDetectRegion::UpdateTime(float delta_time)
	{
		time += delta_time;
	}

}
