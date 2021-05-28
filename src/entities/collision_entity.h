#pragma once

#include "entity.h"
#include "../collision/collision.h"

namespace entities
{
	/*
	 * This class is an entity with a collision box
	 */
	class CollisionEntity : public Entity
	{
	private:
		collision::Box bounding_box;

		glm::vec3 min_xyz;
		glm::vec3 max_xyz;

		void (*on_collide)(const collision::Collision& collision);

	public:
		CollisionEntity(const models::TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation,
			float scale, const collision::Box& bounding_box);

		/*
		 * @brief: A function to do some sort of behaviour when the entity collides
		 *
		 * @param collision: The collision
		 */
		virtual void OnCollide(const collision::Collision& collision);

		/*
		 * @brief: A function to check if the entity is colliding with a point in 3D space
		 *
		 * @param point: The point to check if its colliding with the entity
		 *
		 * @return: True is the entity is colliding, false if not
		 */
		bool IsColliding(const glm::vec3& point) const;

		/*
		 * @brief: A function to check if the entity is colliding with another entity
		 *
		 * @param e: The other entity to check if its colliding with this
		 *
		 * @return: True is the entity is colliding, false if not
		 */
		bool IsColliding(const CollisionEntity& e) const;

		/*
		 * @brief: A function to set the collision behaviour of the entity
		 *
		 * @param function: A function pointer to a function with the collision behaviour
		 */
		void SetCollisionBehaviour(void (*function)(const collision::Collision& collision))
		{ if (function != nullptr) { on_collide = function; } }
	};
}