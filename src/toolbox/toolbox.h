#pragma once

#include "../entities/camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace toolbox
{
	#define WINDOW_WIDTH 1400.0f
	#define WINDOW_HEIGT 800.0f

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
