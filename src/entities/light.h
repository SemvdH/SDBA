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
		glm::vec3 attenuation = { 1, 0, 0 };

	public:
		Light(const glm::vec3& position, const glm::vec3& color) : position(position), color(color) { }
		Light(const glm::vec3& position, const glm::vec3& color, const glm::vec3& attenuation)
			: position(position), color(color), attenuation(attenuation) { }

		glm::vec3 GetPosition() const { return position; }
		void setPosition(const glm::vec3& position) { this->position = position; }
		glm::vec3 GetColor() const { return color; }
		void setColor(const glm::vec3& color) { this->color = color; }
		glm::vec3 GetAttenuation() const { return attenuation; }
		void SetAttenuation(const glm::vec3& attenuation) { this->attenuation = attenuation; }
	};
}
