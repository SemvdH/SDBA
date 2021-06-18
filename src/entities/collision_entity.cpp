#include "collision_entity.h"

namespace entities
{
	CollisionEntity::CollisionEntity(const models::TexturedModel& model, const glm::vec3& position,
		const glm::vec3& rotation, float scale, const collision::Box& bounding_box)
		: Entity(model, position, rotation, scale),
		bounding_box(bounding_box)
	{
		MoveCollisionBox();
	}

	void CollisionEntity::OnCollide(const collision::Collision& collision)
	{
		if (on_collide != nullptr)
		{
			
				on_collide(collision);
			
		}
	}

	bool CollisionEntity::IsColliding(const glm::vec3& point) const
	{
		return (point.x >= min_xyz.x && point.x <= max_xyz.x) &&
			(point.y >= min_xyz.y && point.y <= max_xyz.y) &&
			(point.z >= min_xyz.z && point.z <= max_xyz.z);
	}

	bool CollisionEntity::IsColliding(const CollisionEntity& e) const
	{
		return (min_xyz.x <= e.max_xyz.x && max_xyz.x >= e.min_xyz.x) &&
			(min_xyz.y <= e.max_xyz.y && max_xyz.y >= e.min_xyz.y) &&
			(min_xyz.z <= e.max_xyz.z && max_xyz.z >= e.min_xyz.z);
	}

	void CollisionEntity::MoveCollisionBox()
	{
		bounding_box.center_pos = position;
		
		const glm::vec3 size = bounding_box.size;

		/*min_xyz = { bounding_box.center_pos.x - (0.5 * size.x), bounding_box.center_pos.y, bounding_box.center_pos.z + (0.5 * size.z) };
		max_xyz = { bounding_box.center_pos.x + (0.5 * size.x), bounding_box.center_pos.y + size.y, bounding_box.center_pos.z - (0.5 * size.z) };*/

		min_xyz = bounding_box.center_pos;
		max_xyz = { bounding_box.center_pos.x + size.x, bounding_box.center_pos.y + size.y, bounding_box.center_pos.z - size.z };
	}
}
