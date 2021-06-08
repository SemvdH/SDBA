#include "main_character.h"
#include "../models/Model.h"
#include <iostream>
#include "entity.h"
#include"../renderEngine/Renderer.h"
#include"../renderEngine/obj_loader.h"
#include"../renderEngine/loader.h"
namespace entities
{
	main_character::main_character(const models::TexturedModel& model, const glm::vec3& position,
		const glm::vec3& rotation, float scale, const collision::Box& bounding_box)
		: CollisionEntity(model, position, rotation, scale, bounding_box) {

	}
	glm::vec3 main_character::move(GLFWwindow* window)
	{
		float movement_speed = -1.0f;
		float up_down_speed = -0.2f;
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
		IncreasePosition(glm::vec3(side_speed, up_down_speed, movement_speed));
		if (position.x > 190) position.x = 190;
		else if (position.x < -190) position.x = -190;
		if (position.y > 350) position.y = 350;
		else if (position.y < -40) position.y = -40;
		MoveCollisionBox();
		return glm::vec3(side_speed, up_down_speed, movement_speed );
	}
}


