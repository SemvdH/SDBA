#include "camera.h"

namespace entities
{
	Camera::Camera(const ::glm::vec3& position, const ::glm::vec3& rotation)
		: position(position),
		rotation(rotation)
	{}

	void Camera::Move(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			position.z -= SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			position.z += SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			position.x += SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			position.x -= SPEED;
		}
	}
}
