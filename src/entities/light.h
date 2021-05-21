#pragma once

#include <glm/vec3.hpp>

namespace entities
{
	/*
	 * This class represents a light in the game 
	 */
	
	class Light
	{
	private:
		glm::vec3 position;
		glm::vec3 color;

	public:
		Light(const glm::vec3& position, const glm::vec3& color) : position(position), color(color) { }

		glm::vec3 GetPosition() const { return position; }
		void setPosition(const glm::vec3& position) { this->position = position; }
		glm::vec3 GetColor() const { return color; }
		void setColor(const glm::vec3& color) { this->color = color; }
	};
}
