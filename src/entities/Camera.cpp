#include "camera.h"
#include <iostream>
#include "../toolbox/toolbox.h"

namespace entities
{
	Camera::Camera(const ::glm::vec3& position, const ::glm::vec3& rotation)
		: position(position),
		rotation(rotation)
	{}

	void Camera::Follow(glm::vec3 follow_position) {
		//set position to follow in front of the camera
		follow_position.z += 100;
		//set position to follow a bit lower
		follow_position.y += 50;
		//move position from original position to fiven position with smoothing
		position = toolbox::Lerp(position, follow_position, 0.1);
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
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			up_down_speed -= UP_SPEED;
		}

		position.x += side_speed;
		position.z += movement_speed;
		position.y += up_down_speed;
	}
}
