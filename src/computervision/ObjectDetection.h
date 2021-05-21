#pragma once

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace computervision
{
	class ObjectDetection
	{
	private:

	public:
		ObjectDetection();
		void readWebcam();
		void showWebcam();
		void calculateDifference();

	};


}

