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
