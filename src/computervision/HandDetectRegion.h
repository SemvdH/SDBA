#pragma once

#include <opencv2/core.hpp>
namespace computervision
{
	class HandDetectRegion
	{
	public:
		HandDetectRegion();

		cv::Mat GenerateHandMaskSquare();

		void detectHand(cv::Mat camera_frame);

	private:
		int start_x_pos;
		int start_y_pos;
		int height;
		int width;
	};

}
