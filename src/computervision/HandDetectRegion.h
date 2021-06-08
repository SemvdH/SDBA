#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "async/StaticCameraInstance.h"
#include "calibration/HandCalibrator.h"
#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FingerCount.h"
namespace computervision
{
	class HandDetectRegion
	{
	public:
		HandDetectRegion(std::string id,int x_pos, int y_pos, int width, int height);

		void SetXPos(int x) { start_x_pos = x; }
		void SetYPos(int y) { start_y_pos = y; }
		int GetXPos() { return start_x_pos; }
		int GetYPos() { return start_y_pos; }

		void SetWidth(int width) { region_width = width; }
		void SetHeigth(int height) { region_height = height; }
		int GetWidth() { return region_width; }
		int GetHeight() { return region_height; }

		cv::Mat GenerateHandMaskSquare(cv::Mat img);

		void DetectHand(cv::Mat& camera_frame);

		bool IsHandPresent();

		void CalibrateBackground();
		void CalibrateSkin();

		std::vector<int> CalculateSkinTresholds();

		void setSkinTresholds(std::vector<int>& tresholds);

	private:
		int start_x_pos;
		int start_y_pos;
		int region_height;
		int region_width;
		bool hand_mask_generated;
		bool hand_present;
		cv::Mat frame, frame_out, handMask, foreground, fingerCountDebug;
		BackgroundRemover background_remover;
		SkinDetector skin_detector;
		handcalibration::HandCalibrator hand_calibrator;
		std::string region_id;

		bool DrawHandMask(cv::Mat* input);
	};

}
