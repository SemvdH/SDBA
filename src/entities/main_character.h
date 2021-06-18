#pragma once

#include "collision_entity.h"
#include "../shaders/entity_shader.h"
#include "../computervision/hand_detect_region.h"

namespace entities
{
	/* 
	* This class contains the information about the player model
	*/
	class MainCharacter : public CollisionEntity {
		const int SIDE_SPEED = 40;		//Standard movement speed for left/right movement
		const int UP_SPEED = 100;		//Standard movement speed for up movement
	public:
		/*
		* @brief: Constructor for the main character model
		* 
		* @param model: Model to load in as the player model
		* @param position: Position of the model inside the game window
		* @param rotation: Rotation of the model inside the game window
		* @param scale: Size of the model
		* @param bounding_box: Collision box around the player model
		*/
		MainCharacter(const models::TexturedModel& model, const glm::vec3& position,
			const glm::vec3& rotation, float scale, const collision::Box& bounding_box);
		
		/*
		* @brief: A function to move the character inside the window
		* 
		* @param window: The game window
		* 
		* @return: Vector with the adjusted side_speed, down_speed, and movement_speed
		*/
		void Move(std::vector<computervision::HandDetectRegion*> regions);

		void OnCollide(const collision::Collision& collision) override;

		bool GetOnCollide();

		double UpdateDelta();
	};
}
