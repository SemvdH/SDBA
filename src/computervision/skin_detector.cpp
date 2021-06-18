#include "skin_detector.h"
#include <iostream>

/*
 Author: Pierfrancesco Soffritti https://github.com/PierfrancescoSoffritti
*/

namespace computervision
{
	SkinDetector::SkinDetector(void) {
		hLowThreshold = 0;
		hHighThreshold = 0;
		sLowThreshold = 0;
		sHighThreshold = 0;
		vLowThreshold = 0;
		vHighThreshold = 0;

		calibrated = false;

		skinColorSamplerRectangle1, skinColorSamplerRectangle2;
	}

	void SkinDetector::drawSkinColorSampler(Mat input) {
		int frameWidth = input.size().width, frameHeight = input.size().height;

		int rectangleSize = 25;
		Scalar rectangleColor = Scalar(0, 255, 255);

		skinColorSamplerRectangle1 = Rect(frameWidth / 5, frameHeight / 2, rectangleSize, rectangleSize);
		skinColorSamplerRectangle2 = Rect(frameWidth / 5, frameHeight / 3, rectangleSize, rectangleSize);

		rectangle(
			input,
			skinColorSamplerRectangle1,
			rectangleColor
		);

		rectangle(
			input,
			skinColorSamplerRectangle2,
			rectangleColor
		);
	}

	void SkinDetector::drawSkinColorSampler(Mat input,int x, int y,int width, int height) {
		int frameWidth = width, frameHeight = height;

		int rectangleSize = 25;
		Scalar rectangleColor = Scalar(0, 255, 255);

		skinColorSamplerRectangle1 = Rect(frameWidth / 5 + x, frameHeight / 2 + y, rectangleSize, rectangleSize);
		skinColorSamplerRectangle2 = Rect(frameWidth / 5 + x, frameHeight / 3 + y, rectangleSize, rectangleSize);

		rectangle(
			input,
			skinColorSamplerRectangle1,
			rectangleColor
		);

		rectangle(
			input,
			skinColorSamplerRectangle2,
			rectangleColor
		);
	}


	void SkinDetector::calibrate(Mat input) {

		Mat hsvInput;
		cvtColor(input, hsvInput, CV_BGR2HSV);

		Mat sample1 = Mat(hsvInput, skinColorSamplerRectangle1);
		Mat sample2 = Mat(hsvInput, skinColorSamplerRectangle2);

		calculateThresholds(sample1, sample2);

		calibrated = true;
	}

	std::vector<int> SkinDetector::calibrateAndReturn(Mat input)
	{
		Mat hsvInput;
		cvtColor(input, hsvInput, CV_BGR2HSV);

		Mat sample1 = Mat(hsvInput, skinColorSamplerRectangle1);
		Mat sample2 = Mat(hsvInput, skinColorSamplerRectangle2);

		calibrated = true;
		return calculateAndReturnTresholds(sample1, sample2);

	}

	void SkinDetector::calculateThresholds(Mat sample1, Mat sample2) {
		int offsetLowThreshold = 80;
		int offsetHighThreshold = 30;

		Scalar hsvMeansSample1 = mean(sample1);
		Scalar hsvMeansSample2 = mean(sample2);

		hLowThreshold = min(hsvMeansSample1[0], hsvMeansSample2[0]) - offsetLowThreshold;
		hHighThreshold = max(hsvMeansSample1[0], hsvMeansSample2[0]) + offsetHighThreshold;

		sLowThreshold = min(hsvMeansSample1[1], hsvMeansSample2[1]) - offsetLowThreshold;
		sHighThreshold = max(hsvMeansSample1[1], hsvMeansSample2[1]) + offsetHighThreshold;

		// the V channel shouldn't be used. By ignorint it, shadows on the hand wouldn't interfire with segmentation.
		// Unfortunately there's a bug somewhere and not using the V channel causes some problem. This shouldn't be too hard to fix.
		vLowThreshold = min(hsvMeansSample1[2], hsvMeansSample2[2]) - offsetLowThreshold;
		vHighThreshold = max(hsvMeansSample1[2], hsvMeansSample2[2]) + offsetHighThreshold;
		//vLowThreshold = 0;
		//vHighThreshold = 255;
	}

	std::vector<int> SkinDetector::calculateAndReturnTresholds(Mat sample1, Mat sample2)
	{
		
		calculateThresholds(sample1, sample2);
		std::vector<int> res;
		res.push_back(hLowThreshold);
		res.push_back(hHighThreshold);
		res.push_back(sLowThreshold);
		res.push_back(sHighThreshold);
		res.push_back(vLowThreshold);
		res.push_back(vHighThreshold);
		return res;
	}

	void SkinDetector::setTresholds(std::vector<int>& tresholds)
	{
		if (tresholds.size() != 6)
		{
			std::cout << "tresholds array not the right size!" << std::endl;
			return;
		}

		hLowThreshold = tresholds[0];
		hHighThreshold = tresholds[1];
		sLowThreshold = tresholds[2];
		sHighThreshold = tresholds[3];
		vLowThreshold = tresholds[4];
		vHighThreshold = tresholds[5];

		calibrated = true;
		
	}

	Mat SkinDetector::getSkinMask(Mat input) {
		Mat skinMask;

		if (!calibrated) {
			skinMask = Mat::zeros(input.size(), CV_8UC1);
			return skinMask;
		}

		Mat hsvInput;
		cvtColor(input, hsvInput, CV_BGR2HSV);

		inRange(
			hsvInput,
			Scalar(hLowThreshold, sLowThreshold, vLowThreshold),
			Scalar(hHighThreshold, sHighThreshold, vHighThreshold),
			skinMask);

		performOpening(skinMask, MORPH_ELLIPSE, { 3, 3 });
		dilate(skinMask, skinMask, Mat(), Point(-1, -1), 3);

		return skinMask;
	}

	void SkinDetector::performOpening(Mat binaryImage, int kernelShape, Point kernelSize) {
		Mat structuringElement = getStructuringElement(kernelShape, kernelSize);
		morphologyEx(binaryImage, binaryImage, MORPH_OPEN, structuringElement);
	}
}