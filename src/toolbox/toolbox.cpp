#include "toolbox.h"

namespace toolbox
{
	glm::mat4 CreateModelMatrix(glm::vec3 translation, glm::vec3 rotation, float scale)
	{
		glm::mat4 matrix(1.0f);
		matrix = glm::translate(matrix, translation);
		matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
		return matrix;
	}

	glm::mat4 CreateViewMatrix(entities::Camera& camera)
	{
		glm::mat4 matrix(1.0f);
		matrix = glm::rotate(matrix, glm::radians(camera.GetRotation().x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(camera.GetRotation().y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(camera.GetRotation().z), glm::vec3(0, 0, 1));
		const glm::vec3 negative_cam_pos = glm::vec3(-camera.GetPosition().x, -camera.GetPosition().y, -camera.GetPosition().z);
		matrix = glm::translate(matrix, negative_cam_pos);
		return matrix;
	}
}