#pragma once

#include "../entities/camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace toolbox
{
	// Window macro's
	    #define DEFAULT_WIDTH 1920
		#define DEFAULT_HEIGHT 1080

		// Change these macros to change the window size
		#define WINDOW_WIDTH 1400.0f
		#define WINDOW_HEIGT 800.0f

		#define SCALED_WIDTH (WINDOW_WIDTH/DEFAULT_WIDTH)
		#define SCALED_HEIGHT (WINDOW_HEIGT/DEFAULT_HEIGHT)
	//
	
	/*
	 * @brief: This function will create a model matrix
	 *
	 * @param translation: The position of the model
	 * @param scale: The scale of the model
	 *
	 * @return: The model matrix of the model
	 */
	glm::mat4 CreateModelMatrix(glm::vec2 translation, glm::vec2 scale);
	
	/*
	 * @brief: This function will create a model matrix
	 *
	 * @param translation: The position of the model
	 * @param rotation: The rotation of the model
	 * @param scale: The scale of the model
	 *
	 * @return: The model matrix of the model
	 */
	glm::mat4 CreateModelMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);

	/*
	 * @brief: This function will create a view matrix from the camera's position
	 *
	 * @param camera: The camera the view matrix needs to be made from
	 *
	 * @return: The view matrix
	 */
	glm::mat4 CreateViewMatrix(entities::Camera& camera);

	/*
	* @biref go to one coordinate to another with smooting
	*
	* @param from one coordinate of the start
	* @param to one coordinate of where to go
	* @param amount the amount of smoothing (lower is smoother)
	* 
	* @return coordinate of where to go
	*/
	float Lerp(float from, float to, float amount);

	/*
	* @biref go from one position to another with smoothing
	*
	* @param from position of the start
	* @param to position of where to go
	* @param amount the amount of smoothing (lower is smoother)
	*
	* @return position of where to go
	*/
	glm::vec3 Lerp(glm::vec3 from, glm::vec3 to, float amount);
  
  /*
	 * @brief: This function will return a value between min and max
	 *
	 * @param min: The min value
	 * @param max: The max value
	 *
	 * @return: The random number
	 */
	int Random(const int min, const int max);
}
