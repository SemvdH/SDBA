#include "VideoCapture.h"

namespace videocapture{
	static cv::VideoCapture cap(1);

	cv::VideoCapture getCap() {
		cap.release();

		return cap;
	}
}
