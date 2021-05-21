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
		/**
		 * @brief default constructor of ObjectDetection
		 * 
		 */
		ObjectDetection();
		/**
		 * @brief Initializes the object detection, captures a frame and modifies it
		 *  so it is ready to use for object detection
		 * 
		 * @return return true if webcam is connected, returns false if it isn't
		 */
		bool setup();
		/**
		 * @brief Displays an image of the current webcam-footage
		 * 
		 */
		void showWebcam();
		/**
		 * @brief Calculates the difference between two images
		 *  and outputs an image that only shows the difference
		 * 
		 */
		void calculateDifference();
		/**
		 * @brief Listens for keypresses and handles them
		 * 
		 */
		void detect();

	};


}

