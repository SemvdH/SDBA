#include "VideoCapture.h"
#include <mutex>

namespace videocapture{
	static cv::VideoCapture cap(1);
	static std::mutex mtx;

	cv::VideoCapture getCap() {
		//cap.release();

		return cap;
	}

	std::mutex* getMutex()
	{
		return &mtx;
	}
}
