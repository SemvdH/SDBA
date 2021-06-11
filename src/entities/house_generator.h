#pragma once

#include <deque>
#include <memory>
#include <map>
#include "../models/Model.h"
#include "../collision/collision.h"

namespace entities
{
	enum class FurnitureType
	{
		COUCH,
		TABLE,
		CHAIR,
		PLANT,
		GUITAR,
		BOOKSHELF,
		LAMP,
		CEILING_OBJECTS,
		MISC
	};
	struct FurniturePiece
	{
		FurnitureType type;
		int size;
	};

	struct FurnitureModel
	{
		FurniturePiece furniture;
		std::deque<models::TexturedModel> texture;

		bool operator<(FurnitureModel a)
		{
			return true;
		}
	};

	
	
	class HouseGenerator
	{
	private:
		const float HOUSE_SIZE = 30;
		
		models::TexturedModel house_model;
		models::ModelTexture default_texture;
		
		//std::map<FurniturePiece, std::deque<models::TexturedModel>> furniture_models;
		std::deque<FurnitureModel> furniture_models;
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
		const FurniturePiece* GetRandomFurniturePiece();
		const FurniturePiece* GetFurniturePiece(FurnitureType type);

		/*
		 * @brief: This function loads all the 3D furniture models
		 */
		void GenerateFurnitureModels();

		/*
		 * @brief: This funtion chooses and returns a random furniture of the given furniture type
		 *
		 * @param furniture: The furniture you want to get
		 *
		 * @return: The model of the random furniture of the chosen furniture type
		 */
		models::TexturedModel GetFurnitureModel(const FurniturePiece* furniture);
	};
}
