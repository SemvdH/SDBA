#include "entity.h"

namespace entities
{
	Entity::Entity(const models::TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, float scale)
		: model(model),
		position(position),
		rotation(rotation),
		scale(scale)
	{
	}

	void Entity::IncreasePosition(const glm::vec3& distance)
	{
		position.x += distance.x;
		position.y += distance.y;
		position.z += distance.z;
	}

	void Entity::IncreaseRotation(const glm::vec3& rotation)
	{
		this->rotation.x += rotation.x;
		this->rotation.y += rotation.y;
		this->rotation.z += rotation.z;
	}


}

