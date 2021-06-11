#pragma once

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "../entities/entity.h"

namespace collision
{
	/*
	 * This structure represents a collision box inside the world.
	 *
	 * center_pos:	The center position of the collision box
	 * size:		The size in each axis of the collision box
	 */
	struct Box
	{
		glm::vec3 center_pos;
		glm::vec3 size;

		void SetRotation(float angle)
		{
			double sinTheta = glm::sin(glm::radians(angle));
			double cosTheta = glm::cos(glm::radians(angle));

			float x = size.x * cosTheta + size.z * sinTheta;
			float z = size.z * cosTheta - size.x * sinTheta;
			
			size.x = x < 0 ? -x : x;
			size.z = z < 0 ? -z : z;
		}
	};

	/*
	 * This structure represents a collision between 2 entities
	 *
	 * entity1:		The first entity
	 * entity2:		The second entity
	 */
	struct Collision
	{
		entities::Entity& entity1;
		entities::Entity& entity2;
	};
}