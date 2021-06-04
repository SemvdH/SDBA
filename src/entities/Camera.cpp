#include "camera.h"

namespace entities
{
	Camera::Camera(const ::glm::vec3& position, const ::glm::vec3& rotation)
		: position(position),
		rotation(rotation)
	{}

	void Camera::Follow(glm::vec3 follow_position) {
		position.z = follow_position.z + 200;
	}

	void Camera::Move(GLFWwindow* window)
	{
		float movement_speed = 0;
		float up_down_speed = 0;
		float side_speed = 0;
		
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
			side_speed += SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			side_speed -= SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			up_down_speed += UP_SPEED;
		}

		position.x += side_speed;
		position.z += movement_speed;
		position.y += up_down_speed;
	}
}
