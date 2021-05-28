#pragma once

#include <iostream>
#include "collision_entity.h"

namespace entities
{
	class Player : public CollisionEntity
	{
	public:
		Player(const models::TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, float scale,
			const collision::Box& bounding_box)
			: CollisionEntity(model, position, rotation, scale, bounding_box)
		{}

		void Update()
		{
			position.x += 0.11f;
			MoveCollisionBox();
		}

		void OnCollide(const ::collision::Collision& collision) override
		{
			std::cout << "Player got HIT" << std::endl;
		}
	};

	class Player2 : public CollisionEntity
	{
	public:
		Player2(const models::TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, float scale,
			const collision::Box& bounding_box)
			: CollisionEntity(model, position, rotation, scale, bounding_box)
		{}

		void Update() { position.x -= 0.01f; MoveCollisionBox(); }

		void OnCollide(const ::collision::Collision& collision) override
		{
			std::cout << "Player2 got HIT" << std::endl;
		}
	};
}
