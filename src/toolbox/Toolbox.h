#pragma once

#include "../entities/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace toolbox
{
	#define WINDOW_WIDTH 1400.0f
	#define WINDOW_HEIGT 800.0f
	
	glm::mat4 createModelMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);

	glm::mat4 createViewMatrix(entities::Camera& camera);
}
