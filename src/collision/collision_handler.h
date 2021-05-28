#pragma once

#include <vector>
#include "../entities/collision_entity.h"
#include "collision.h"

namespace collision
{
	/*
	 * @brief: This function will check all the collision entities for
	 *         collisions and call the OnCollide function when a entity collides.
	 *
	 * @param entities: A list with all the collision entities.
	 */
	void CheckCollisions(std::vector<entities::CollisionEntity*>& entities);
}