#pragma once
#include"opencv2\opencv.hpp"
#include <opencv2/imgproc\types_c.h>
/*
 Author: Pierfrancesco Soffritti https://github.com/PierfrancescoSoffritti
*/
namespace computervision
{
using namespace cv;
using namespace std;

	class BackgroundRemover {
	public:
		BackgroundRemover(void);
		void calibrate(Mat input);
		Mat getForeground(Mat input);

	private:
		Mat background;
		bool calibrated = false;

		Mat getForegroundMask(Mat input);
		void removeBackground(Mat input, Mat background);
	};
}