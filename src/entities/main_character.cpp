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

	Entity main_character::loadCharacter()
	{
		models::RawModel raw_model = render_engine::LoadObjModel("res/beeTwo.obj");
		models::ModelTexture texture = { render_engine::loader::LoadTexture("res/Texture.png") };
		texture.shine_damper = 10;
		texture.reflectivity = 0;
		models::TexturedModel model = { raw_model, texture };
		entities::Entity entity(model, glm::vec3(0, -50, -100), glm::vec3(0, 90, 0), 5);
		return entity;
	}
	glm::vec3 main_character::move(GLFWwindow* window)
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
		return glm::vec3(side_speed, movement_speed, up_down_speed);
	}
}


