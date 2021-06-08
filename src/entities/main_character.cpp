#include "main_character.h"
#include "../models/Model.h"
#include <iostream>
#include "entity.h"
#include"../renderEngine/Renderer.h"
#include"../renderEngine/obj_loader.h"
#include"../renderEngine/loader.h"
namespace entities
{
	MainCharacter::MainCharacter(const models::TexturedModel& model, const glm::vec3& position,
		const glm::vec3& rotation, float scale, const collision::Box& bounding_box)
		: CollisionEntity(model, position, rotation, scale, bounding_box) 
	{}

	glm::vec3 MainCharacter::Move(GLFWwindow* window)
	{
		float movement_speed = -1.0f;	//Forward speed adjustment, bee is moving at a standard speedrate
		float down_speed = -1.0f;		//Down speed adjustment, downspeed is difference between down_speed and UP_SPEED	
		float side_speed = 0;			//Side speed adjustment

		//For gameplay with use of keyboard keys: W, A, S, D
		//W: Go forward
		//A: Go left
		//S: Go backwards
		//D: Go right
		//TODO Implement CV actions 
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			movement_speed -= SIDE_SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			movement_speed += SIDE_SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			side_speed += SIDE_SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			side_speed -= SIDE_SPEED;
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			down_speed += UP_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			down_speed -= UP_SPEED;
		}
		IncreasePosition(glm::vec3(side_speed, down_speed, movement_speed));
		
		//Use only for binding bee to house, such that it doesn't go outside of the room.
		//TODO delete when boundingbox is implemented!
		if (position.x > 190) position.x = 190;
		else if (position.x < -190) position.x = -190;
		if (position.y > 350) position.y = 350;
		else if (position.y < -40) position.y = -40;
		
		//Move player bounding box according to the position on screen
		MoveCollisionBox();
		return glm::vec3(side_speed, down_speed, movement_speed );
	}
}