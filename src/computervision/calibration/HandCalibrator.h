#pragma once
#include <opencv2/core/base.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace computervision
{
	namespace handcalibration
	{
		enum class HandDetectionType
		{
			MENU,
			GAME
		};

		class HandCalibrator
		{
		public:
			HandCalibrator();

			

			/**
			 * @brief draws the text to show the status of the calibration on the image
			 *
			 * @param output_frame the frame to draw on.
			 */
			void DrawHandCalibrationText(cv::Mat& output_frame);

			/**
			 * @brief sets the skin calibration variable.
			 *
			 * @param val the value to set
			 */
			void SetSkinCalibration(bool val);

			/**
			 * @brief sets the background calibration variable.
			 *
			 * @param val the value to set
			 */
			void SetBackGroundCalibrated(bool val);

			/**
			 * @brief sets the value for if the hand is present.
			 * 
			 * @param val the value to set.
			 */
			void SetHandPresent(bool val);

			/**
			 * @brief checks if the hand is present in the given image
			 * 
			 * @param input_image the input image to check.
			 */
			bool CheckIfHandPresent(cv::Mat input_image, HandDetectionType type);

			/**
			 * @brief sets the amount of fingers that are currently detected.
			 * 
			 * @param amount the amount of fingers.
			 */
			void SetAmountOfFingers(int amount);

		private:

			bool background_calibrated;
			bool skintone_calibrated;
			bool hand_present;
			int fingers_amount;
		};

	}
}
