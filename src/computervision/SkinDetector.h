#pragma once

#include <opencv2\core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
/*
 Author: Pierfrancesco Soffritti https://github.com/PierfrancescoSoffritti
*/

namespace computervision
{
	using namespace cv;
	using namespace std;

	class SkinDetector {
	public:
		SkinDetector(void);

		/*
		* @brief draws the positions in where the skin color will be sampled.
		* 
		* @param input the input matrix to sample the skin color from
		*/
		void drawSkinColorSampler(Mat input);

		/*
		* @brief calibrates the skin color detector with the given input frame
		* 
		* @param input the input frame to calibrate from
		*/
		void calibrate(Mat input);

		/*
		* @brief gets the mask for the hand
		* 
		* @param input the input matrix to get the skin mask from
		* @returns the skin mask in a new matrix
		*/
		Mat getSkinMask(Mat input);

	private:
		int hLowThreshold = 0;
		int hHighThreshold = 0;
		int sLowThreshold = 0;
		int sHighThreshold = 0;
		int vLowThreshold = 0;
		int vHighThreshold = 0;

		bool calibrated = false;

		// rectangles that get drawn to show where the skin color will be sampled
		Rect skinColorSamplerRectangle1, skinColorSamplerRectangle2;

		/*
		* @brief calculates the skin tresholds for the given samples
		* 
		* @param sample1 the first sample
		* @param sample2 the second sample
		*/
		void calculateThresholds(Mat sample1, Mat sample2);

		/**
		 * @brief the opening. it generates the structuring element and performs the morphological transformations required to detect the hand.
		 * This needs to be done to get the skin mask.
		 * 
		 * @param binaryImage the matrix to perform the opening on. This needs to be a binary image, so consisting of only 1's and 0's.
		 * @param structuralElementShape the shape to use for the kernel that is used with generating the structuring element
		 * @param structuralElementSize the size of the kernel that will be used with generating the structuring element.
		 */
		void performOpening(Mat binaryImage, int structuralElementShape, Point structuralElementSize);
	};
}