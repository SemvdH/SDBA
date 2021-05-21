#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/objdetect.hpp>
#include <opencv2/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
/*
 Author: Pierfrancesco Soffritti https://github.com/PierfrancescoSoffritti
*/

using namespace cv;
using namespace std;

namespace computervision
{
	class FaceDetector {
	public:
		FaceDetector(void);
		void removeFaces(Mat input, Mat output);
	};
}