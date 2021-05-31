#include "VideoCapture.h"
#include <mutex>
#include <iostream>

namespace videocapture{
	static cv::VideoCapture cap(0);
	static std::mutex mtx;

	cv::VideoCapture getCap() {
		cap.release();

		return cap;
	}

	cv::Mat readFrame()
	{
		std::cout << "reading frame" << std::endl;
		cv::Mat camFrame, videoFrame;

		mtx.lock();
		bool res = cap.read(camFrame);
		std::cout << (res ? "reading worked" : "reading failed") << std::endl;
		videoFrame = camFrame.clone();
		mtx.unlock();

		return videoFrame;
	}

	std::mutex* getMutex()
	{
		return &mtx;
	}
}
