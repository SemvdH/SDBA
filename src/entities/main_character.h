#pragma once

#include "collision_entity.h"
#include "../shaders/entity_shader.h"

namespace entities
{
	class main_character : public CollisionEntity {
		const float SPEED = 1.0f;
		const float UP_SPEED = 0.6f;
	public:
		main_character(const models::TexturedModel& model, const glm::vec3& position,
			const glm::vec3& rotation, float scale, const collision::Box& bounding_box);
		glm::vec3 move(GLFWwindow* window);
	};
}
