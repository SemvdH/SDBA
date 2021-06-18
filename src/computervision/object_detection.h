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
		 * @brief Displays an image of the current webcam-footage
		 * 
		 */
		void ShowWebcam();
		/**
		 * @brief Calculates the difference between two images
		 *  and outputs an image that only shows the difference
		 * 
		 */
		void CalculateDifference();

		/**
		 * @brief generates the square that will hold the mask in which the hand will be detected.
		 * 
		 * @param img the current camear frame
		 * @return a matrix containing the mask
		 */
		cv::Mat GenerateHandMaskSquare(cv::Mat img);

		/**
		 * @brief reads the camera and returns it in a matrix.
		 * 
		 * @return the camera frame in a matrix
		 */
		cv::Mat ReadCamera();

		/**
		 * @brief detects a hand based on the given hand mask input frame.
		 * 
		 * @param inputFrame the input frame from the camera
		 * @param hand_present boolean that will hold true if the hand is detected, false if not.
		 * @return true if hand is open, false if hand is closed
		 */
		bool DetectHand(cv::Mat camera_frame, bool& hand_present);

		/**
		 * @brief draws the hand mask rectangle on the given input matrix.
		 * 
		 * @param input the input matrix to draw the rectangle on
		 */
		bool DrawHandMask(cv::Mat *input);

		/**
		 * @brief checks if the hand of the user is open.
		 * 
		 * @return true if the hand is open, false if not.
		 */
		bool IsHandOpen();


		/**
		 * @brief checks whether the hand is held within the detection square.
		 * 
		 * @return true if the hand is in the detection square, false if not.
		 */
		bool IsHandPresent();

		cv::VideoCapture GetCap();

	private:
		bool is_hand_open;
		bool is_hand_present;
		void UpdateTime();

	};


}

