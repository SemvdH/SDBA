
#include "HandCalibrator.h"

#define MIN_MENU_HAND_SIZE 10000
#define MIN_GAME_HAND_SIZE 10000 // todo change
namespace computervision
{
	namespace handcalibration
	{

		HandCalibrator::HandCalibrator()
		{

		}

		void HandCalibrator::DrawHandCalibrationText(cv::Mat& output_frame)
		{
			cv::rectangle(output_frame, cv::Rect(0, 0, output_frame.cols, 40), cv::Scalar(0, 0, 0), -1);
			cv::putText(output_frame, "Hand calibration", cv::Point(output_frame.cols / 2 - 100, 25), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(18, 219, 65), 2);
			cv::putText(output_frame, "press 'b' to calibrate background,then press 's' to calibrate skin tone", cv::Point(5, 35), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(18, 219, 65), 1);

			cv::rectangle(output_frame, cv::Rect(0, output_frame.rows - 80, 450, output_frame.cols), cv::Scalar(0, 0, 0), -1);

			cv::putText(output_frame, "hand in frame:", cv::Point(5, output_frame.rows - 50), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(255, 255, 0), 1);
			cv::rectangle(output_frame, cv::Rect(420, output_frame.rows - 67, 15, 15), hand_present ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), -1);

			cv::putText(output_frame, "background calibrated:", cv::Point(5, output_frame.rows - 30), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(255, 255, 0), 1);
			cv::rectangle(output_frame, cv::Rect(420, output_frame.rows - 47, 15, 15), background_calibrated ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), -1);

			cv::putText(output_frame, "skin color calibrated:", cv::Point(5, output_frame.rows - 10), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(255, 255, 0), 1);
			cv::rectangle(output_frame, cv::Rect(420, output_frame.rows - 27, 15, 15), skintone_calibrated ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), -1);

			if (hand_present)
			{
				std::string hand_text = fingers_amount > 0 ? "open" : "closed";
				cv::putText(output_frame, hand_text, cv::Point(10, 75), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(255, 0, 255), 3);
			}
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

		void HandCalibrator::SetAmountOfFingers(int amount)
		{
			fingers_amount = amount;
		}

		bool HandCalibrator::CheckIfHandPresent(cv::Mat input_image, HandDetectionType type)
		{
			std::vector<std::vector<cv::Point>> points;
			cv::findContours(input_image, points, cv::RetrievalModes::RETR_LIST, cv::ContourApproximationModes::CHAIN_APPROX_SIMPLE);

			if (points.size() == 0) return false;

			for (int p = 0; p < points.size(); p++)
			{
				int area = cv::contourArea(points[p]);
				if (type == handcalibration::HandDetectionType::MENU)
					if (area > MIN_MENU_HAND_SIZE) return true;

				if (type == handcalibration::HandDetectionType::GAME)
					if (area > MIN_GAME_HAND_SIZE) return true;
			}

			return false;
		}




	}
}
