#pragma once

#include <opencv2/core.hpp>
namespace computervision
{
	/**
	 * @brief checks if the hand is present in the input image.
	 * 
	 * @param input_image the image to check
	 * @return true if the hand was found, false if not
	 */
	bool CheckIfHandPresent(cv::Mat input_image);
}
