#include "camera.h"

namespace entities
{
	Camera::Camera(const ::glm::vec3& position, const ::glm::vec3& rotation)
		: position(position),
		rotation(rotation)
	{}

	void Camera::Move(GLFWwindow* window)
	{
		float movement_speed = 0;
		
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			movement_speed -= SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			movement_speed += SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			rotation.y += ROT_SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			rotation.y -= ROT_SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			//rotation.x -= ROT_SPEED;
			position.y += 5;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			//rotation.x += ROT_SPEED;
			position.y -= 5;
		}

		float dx = glm::cos(glm::radians(rotation.y + 90)) * movement_speed;
		float dz = glm::sin(glm::radians(rotation.y + 90)) * movement_speed;

		position.x += dx;
		position.z += dz;
	}
}
