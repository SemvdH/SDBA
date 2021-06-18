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

		/**
		 * @brief constructor, 
		 * create background variable and set calibrated to faslse
		 * 
		 */
		BackgroundRemover(void);

		/**
		 * @brief sets the input image to a grayscale image
		 * sets calibrated to true
		 * 
		 * @param input input the image that has to be calibrated
		 */
		void calibrate(Mat input);

		/**
		 * @brief Gets the mask of the foregorund of the input image
		 * and copies it to another image
		 * 
		 * @param input The image from which the forground needs to be picked
		 * @return The image on which te foregroundmask is copied
		 */
		Mat getForeground(Mat input);

	private:
		Mat background;
		bool calibrated = false;

		/**
		 * @brief Sets the image to grayscale and removes the background
		 * 
		 * @param input The image from which the forground needs to be picked
		 * @return The mask of the foreground of the image 
		 */
		Mat getForegroundMask(Mat input);
		/**
		 * @brief makes everything on the background black
		 * 
		 * @param input the image from which the background needs to be removed
		 * @param background the background of the image
		 */
		void removeBackground(Mat input, Mat background);
	};
}