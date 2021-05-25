#pragma once

#include "../entities/camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace toolbox
{
	#define WINDOW_WIDTH 1400
	#define WINDOW_HEIGT 800
	
	glm::mat4 CreateModelMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);

	glm::mat4 CreateViewMatrix(entities::Camera& camera);
}
