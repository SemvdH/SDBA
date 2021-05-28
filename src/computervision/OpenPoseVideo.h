#pragma once

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

namespace computervision
{
	class OpenPoseVideo{
	private:

	public:
		void movementSkeleton(Mat inputImage);
		void setup();
	};
}
