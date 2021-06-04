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
		#define WINDOW_HEIGHT 800.0f

		#define SCALED_WIDTH (WINDOW_WIDTH/DEFAULT_WIDTH)
		#define SCALED_HEIGHT (WINDOW_HEIGHT/DEFAULT_HEIGHT)
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
}
