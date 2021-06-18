#pragma once

#include <deque>
#include <memory>
#include <map>

#include "collision_entity.h"
#include "../models/Model.h"
#include "../collision/collision.h"
#include "../model_Storage.h"

namespace entities
{
	class HouseGenerator
	{
	private:
		const float HOUSE_SIZE = 30;
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
		void GenerateHouse(std::deque<std::shared_ptr<CollisionEntity>>* furniture_list, const glm::vec3& position, float y_rotation);

		/*
		 * @brief: Returns the depth of the house (chunk)
		 */
		float GetHouseDepth() const { return singleton::Model_Storage::get_instance()->get_house_model().raw_model.model_size.x * HOUSE_SIZE; }
	
	private:
		void GetRandomFurniturePiece(singleton::FurniturePiece* furniture_piece);
		void GetFurniturePiece(singleton::FurnitureType type, singleton::FurniturePiece* furniture_piece);

		/*
		 * @brief: This funtion chooses and returns a random furniture of the given furniture type
		 *
		 * @param furniture: The furniture you want to get
		 *
		 * @return: The model of the random furniture of the chosen furniture type
		 */
		models::TexturedModel GetFurnitureModel(const singleton::FurniturePiece* furniture);
	};
}
