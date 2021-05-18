#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "../models/Model.h"

namespace entities
{
	class Entity
	{
	private:
		models::TexturedModel model;
		glm::vec3 position;
		glm::vec3 rotation;
		float scale;

	public:
		Entity(const models::TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, float scale);

		void increasePosition(const glm::vec3& distance);
		void increaseRotation(const glm::vec3& rotation);
		
		inline models::TexturedModel getModel() const{return model;}
		inline void set_model(const ::models::TexturedModel& model) { this->model = model; }
		inline glm::vec3 getPosition() const { return position; }
		inline void set_position(const ::glm::vec3& position) {	this->position = position; }
		inline glm::vec3 getRotation() const { return rotation; }
		inline void set_rotation(const ::glm::vec3& rotation) { this->rotation = rotation; }
		inline float getScale() const {	return scale; }
		inline void set_scale(const float scale) { this->scale = scale; }
	};
}