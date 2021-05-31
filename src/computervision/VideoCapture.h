#pragma once
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <mutex>

namespace videocapture {
	cv::VideoCapture getCap();
	std::mutex* getMutex();

}
