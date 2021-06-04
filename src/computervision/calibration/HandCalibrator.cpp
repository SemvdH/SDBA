
#include "HandCalibrator.h"

#define MIN_HAND_SIZE 10000
namespace computervision
{
	namespace handcalibration
	{

		static bool background_calibrated;
		static bool skintone_calibrated;
		static bool hand_present;

		HandCalibrator::HandCalibrator()
		{

		}

		void HandCalibrator::DrawHandCalibrationText(cv::Mat& output_frame)
		{
			cv::rectangle(output_frame,cv::Rect(0, 0, output_frame.cols, 40),cv::Scalar(0,0,0),-1);
			cv::putText(output_frame, "Hand calibration", cv::Point(output_frame.cols/2-100, 25), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(18, 219, 65), 2);
			cv::putText(output_frame, "press 'b' to calibrate background,then press 's' to calibrate skin tone", cv::Point(5, 35), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(18, 219, 65), 1);

			cv::putText(output_frame, "hand in frame:", cv::Point(5, output_frame.rows - 50), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(255, 255, 0), 1);
			cv::rectangle(output_frame, cv::Rect(270, output_frame.rows - 70, 20, 20),  hand_present ? cv::Scalar(0, 255, 0) : cv::Scalar(0,0,255), -1);


			cv::putText(output_frame, (background_calibrated ? "background calibrated" : "background not calibrated"), cv::Point(5, output_frame.rows-30), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(255, 255, 0), 1);
			cv::putText(output_frame, (skintone_calibrated ? "skincolor calibrated" : "skincolor not calibrated"), cv::Point(5, output_frame.rows-10), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(255, 255, 0), 1);
		}

		void HandCalibrator::SetSkinCalibration(bool val)
		{
			skintone_calibrated = val;
		}

		void HandCalibrator::SetBackGroundCalibrated(bool val)
		{
			background_calibrated = val;
		}

		void HandCalibrator::SetHandPresent(bool val)
		{
			hand_present = val;
		}

		bool HandCalibrator::CheckIfHandPresent(cv::Mat input_image)
		{
			std::vector<std::vector<cv::Point>> points;
			cv::findContours(input_image, points, cv::RetrievalModes::RETR_LIST, cv::ContourApproximationModes::CHAIN_APPROX_SIMPLE);

			if (points.size() == 0) return false;

			for (int p = 0; p < points.size(); p++)
			{
				int area = cv::contourArea(points[p]);
				if (area > MIN_HAND_SIZE) return true;
			}

			return false;
		}




	}
}
