#pragma once

#include <deque>
#include <memory>
#include <map>
#include "../models/Model.h"
#include "../collision/collision.h"

namespace entities
{
	enum class Furniture
	{
		COUCH
	};
	
	class HouseGenerator
	{
	private:
		const float HOUSE_SIZE = 30;
		
		models::TexturedModel house_model;
		models::ModelTexture default_texture;
		
		std::map<Furniture, std::deque<models::TexturedModel>> furniture_models;

	public:
		HouseGenerator();

		/*
		 * @brief: This function generates a house with furniture at the given position and rotation
		 *
		 * @param position: The position of the house to render
		 * @param y_rotation: The y rotation the house needs to be rendered with
		 *
		 * @return: A list with all the entities of the generated house (the furniture)
		 */
		std::deque<std::shared_ptr<Entity>> GenerateHouse(const glm::vec3& position, float y_rotation);

		/*
		 * @brief: Returns the depth of the house (chunk)
		 */
		float GetHouseDepth() const { return house_model.raw_model.model_size.x * HOUSE_SIZE; }
	
	private:
		void GenerateFurnitureModels();

		models::TexturedModel GetFurnitureModel(Furniture furniture);
	};
}
