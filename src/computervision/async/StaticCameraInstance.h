#pragma once
#include <opencv2/videoio.hpp>

namespace static_camera
{

	static cv::VideoCapture getCap()
	{
		static cv::VideoCapture cap(0);
		return cap;
	}
};
