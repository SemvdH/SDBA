#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <GLFW/glfw3.h>

#include "async/StaticCameraInstance.h"
#include "calibration/HandCalibrator.h"
#include "background_remover.h"
#include "skin_detector.h"
#include "finger_count.h"
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
		void UpdateTime(float delta_time);
		void SetMainSkinDetecRegion(bool val) { is_main_skin_detection_region = val; };
		void SetSkinTimerCallback(std::function<void()> fun) { skin_timer_callback = fun; };

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

		float time = 0;
		int seconds_left = 5; // calibration countdown

		bool background_calibrated = false;
		bool skin_calibrated = false;
		bool is_main_skin_detection_region = false;
		std::function<void()> skin_timer_callback;


		
	};

}
