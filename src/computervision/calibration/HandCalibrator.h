#pragma once
#include <opencv2/core/base.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace computervision
{
	namespace handcalibration
	{
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

			bool CheckIfHandPresent(cv::Mat input_image);

			void SetHandPresent(bool val);
		};

	}
}
