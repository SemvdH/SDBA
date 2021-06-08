
#include "HandDetectRegion.h"

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

		// detect skin color
		skin_detector.drawSkinColorSampler(camera_frame,start_x_pos,start_y_pos,region_width,region_height);

		// remove background from image
		foreground = background_remover.getForeground(input_frame);

		// detect the hand contours
		handMask = skin_detector.getSkinMask(foreground);

		// draw the hand rectangle on the camera input, and draw text showing if the hand is open or closed.
		DrawHandMask(&camera_frame);

		//imshow("output" + region_id, frame_out);
		//imshow("foreground" + region_id, foreground);
		imshow("handMask" + region_id, handMask);
		/*imshow("handDetection", fingerCountDebug);*/

		hand_present = hand_calibrator.CheckIfHandPresent(handMask,handcalibration::HandDetectionType::GAME);
		std::string text = (hand_present ? "hand" : "no");
		cv::putText(camera_frame, text, cv::Point(start_x_pos, start_y_pos), cv::FONT_HERSHEY_COMPLEX, 2.0, cv::Scalar(0, 255, 255), 2);
		hand_calibrator.SetHandPresent(hand_present);

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
		rectangle(*input, Rect(start_x_pos, start_y_pos, region_width, region_height), Scalar(255, 255, 255));
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
		return skin_detector.calibrateAndReturn(frame_out);
	}

	void HandDetectRegion::setSkinTresholds(std::vector<int>& tresholds)
	{
		std::cout << "setting skin " << region_id << std::endl;
		skin_detector.setTresholds(tresholds);
	}

}
