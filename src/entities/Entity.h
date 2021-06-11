#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "../models/model.h"

namespace entities
{
	/*
	 * This class represents a movable model in the game
	 */
	
	class Entity
	{
	protected:
		models::TexturedModel model;
		
		glm::vec3 position;
		glm::vec3 rotation;
		float scale;

	public:
		Entity(const models::TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, float scale);

		/*
		 * @brief: This function increases the position of the entity
		 *
		 * @param distance: The amount of distance in each axis the entity needs to move
		 */
		void IncreasePosition(const glm::vec3& distance);

		/*
		 * @brief: This function increases the rotation of the entity
		 *
		 * @param rotation: The angle of each axis the entity needs to rotate
		 */
		void IncreaseRotation(const glm::vec3& rotation);
		
		inline models::TexturedModel GetModel() const{return model;}
		inline void SetModel(const ::models::TexturedModel& model) { this->model = model; }
		inline glm::vec3 GetPosition() const { return position; }
		inline void SetPosition(const ::glm::vec3& position) {	this->position = position; }
		inline glm::vec3 GetRotation() const { return rotation; }
		void SetRotation(const ::glm::vec3& rotation) { this->rotation = rotation; }
		inline float GetScale() const {	return scale; }
		inline void SetScale(const float scale) { this->scale = scale; }
	};
}