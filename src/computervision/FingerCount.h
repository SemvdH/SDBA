#pragma once

#include "opencv2/core.hpp"
#include <opencv2/imgproc/types_c.h>

/*
 Author: Nicolò Castellazzi https://github.com/nicast
*/

namespace computervision
{
	using namespace cv;
	using namespace std;

	class FingerCount {
	public:
		FingerCount(void);
		/**
		 * @brief gets the amount of fingers that are held up.
		 * 
		 * @param input_image the source image to find the fingers on. It should be a mask of a hand
		 * @param frame the frame to draw the resulting values on (how many fingers are held up etc)
		 * @return a new image with all the data drawn on it.
		 */
		Mat findFingersCount(Mat input_image, Mat frame);

	private:
		// colors to use
		Scalar color_blue;
		Scalar color_green;
		Scalar color_red;
		Scalar color_black;
		Scalar color_white;
		Scalar color_yellow;
		Scalar color_purple;

		/**
		 * @brief finds the distance between 2 points.
		 * 
		 * @param a the first point
		 * @param b the second point
		 * @return a double representing the distance
		 */
		double findPointsDistance(Point a, Point b);

		/**
		 * @brief compacts the given points on their medians. 
		 * what it does is for each point, it checks if the distance to it's neighbour is greater than the 
		 * max distance. If so, it just adds it to the list that is returned. If not, it calculates the 
		 * median and adds it to the returned list
		 * 
		 * @param points the points to compact
		 * @param max_neighbor_distance the maximum distance between points
		 * @return a vector with the points now compacted.
		 */
		vector<Point> compactOnNeighborhoodMedian(vector<Point> points, double max_neighbor_distance);
		
		/**
		 * @brief finds the angle between 3 different points.
		 * 
		 * @param a the first point
		 * @param b the second point
		 * @param c the third point
		 * @return the angle between the 3 points
		 */
		double findAngle(Point a, Point b, Point c);

		/**
		 * @brief checks if the given points make up a finger.
		 * 
		 * @param a the first point to check for
		 * @param b the second point to check for
		 * @param c the third point to check for
		 * @param limit_angle_inf the limit of the angle between 2 fingers
		 * @param limit_angle_sup the limit of the angle between a finger and a convex point
		 * @param palm_center the center of the palm
		 * @param distance_from_palm_tollerance the distance from the palm tolerance
		 * @return true if the points are a finger, false if not.
		 */
		bool isFinger(Point a, Point b, Point c, double limit_angle_inf, double limit_angle_sup, cv::Point palm_center, double distance_from_palm_tollerance);
		
		/**
		 * @brief finds the closest point to the given point that is in the given list.
		 * 
		 * @param points the points to check for
		 * @param pivot the pivot to check against
		 * @return a vector containing the point that is closest
		 */
		vector<Point> findClosestOnX(vector<Point> points, Point pivot);

		/**
		 * @brief finds the distance between the x coords of the points.
		 * 
		 * @param a the first point
		 * @param b the second point
		 * @return the distance between the x values
		 */
		double findPointsDistanceOnX(Point a, Point b);

		/**
		 * @brief draws the points on the image.
		 * 
		 * @param image the image to draw on
		 * @param points the points to draw
		 * @param color the color to draw them with
		 * @param with_numbers if the numbers should be drawn with the points
		 */
		void drawVectorPoints(Mat image, vector<Point> points, Scalar color, bool with_numbers);
	};
}