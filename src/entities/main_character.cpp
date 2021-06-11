#include "main_character.h"
#include "../models/Model.h"
#include <iostream>
#include "entity.h"
#include"../renderEngine/Renderer.h"
#include"../renderEngine/obj_loader.h"
#include"../renderEngine/loader.h"
namespace entities
{
	float movement_speed;	
	float down_speed;		
	float side_speed;
	bool is_playing;

	MainCharacter::MainCharacter(const models::TexturedModel& model, const glm::vec3& position,
		const glm::vec3& rotation, float scale, const collision::Box& bounding_box)
		: CollisionEntity(model, position, rotation, scale, bounding_box) 
	{
		is_playing = true;
	}

	void MainCharacter::Move(std::vector<computervision::HandDetectRegion*> regions)
	{
		computervision::HandDetectRegion* reg_left = regions.at(0);
		computervision::HandDetectRegion* reg_up = regions.at(1);
		computervision::HandDetectRegion* reg_right = regions.at(2);

		if (is_playing) {
			movement_speed = -0.5f;	//Forward speed adjustment, bee is moving at a standard speedrate
			down_speed = -1.0f;		//Down speed adjustment, downspeed is difference between down_speed and UP_SPEED	
			side_speed = 0;			//Side speed adjustment

			//For gameplay with use of keyboard keys: W, A, S, D
			//W: Go forward
			//A: Go left
			//S: Go backwards
			//D: Go right
			//TODO Implement CV actions 
			//top right
			if (reg_up->IsHandPresent() && reg_left->IsHandPresent())
			{
				side_speed += SIDE_SPEED;
				down_speed += UP_SPEED;
			}
			//right
			if (reg_left->IsHandPresent())
			{
				side_speed += SIDE_SPEED;
			}
			//top left
			if (reg_up->IsHandPresent() && reg_right->IsHandPresent())
			{
				down_speed += UP_SPEED;
				side_speed -= SIDE_SPEED;
			}
			//left
			if (reg_right->IsHandPresent())
			{
				side_speed -= SIDE_SPEED;
			}

			if (reg_up->IsHandPresent())
			{
				down_speed += UP_SPEED;
				SetRotation(glm::vec3(10, 90, 0));
			}
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
			if (reg_right->IsHandPresent() && reg_left->IsHandPresent())
			{
				is_playing = true;
			}
	}

	void MainCharacter::OnCollide(const collision::Collision& collision) {
		down_speed = -2.0f;
		movement_speed = 0.0f;
		is_playing = false;
		std::cout << "collision" << std::endl;
	}
}