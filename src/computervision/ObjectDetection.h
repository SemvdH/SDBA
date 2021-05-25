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

		/**
		 * @brief generates the square that will hold the mask in which the hand will be detected.
		 * 
		 * @param img the current camear frame
		 * @return a matrix containing the mask
		 */
		cv::Mat generateHandMaskSquare(cv::Mat img);

		/**
		 * @brief reads the camera and returns it in a matrix.
		 * 
		 * @return the camera frame in a matrix
		 */
		cv::Mat readCamera();

		/**
		 * @brief detects a hand based on the given hand mask input frame.
		 * 
		 * @param inputFrame the input frame with only the hand
		 * @return true if the webcam is connected, false if not.
		 */
		bool detectHand(cv::Mat inputFrame);

		/**
		 * @brief draws the hand mask rectangle on the given input matrix.
		 * 
		 * @param input the input matrix to draw the rectangle on
		 */
		bool drawHandMaskRect(cv::Mat *input);

	};


}

