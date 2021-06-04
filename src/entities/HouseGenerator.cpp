#include "HouseGenerator.h"
#include "../renderEngine/obj_loader.h"
#include "../renderEngine/Loader.h"

namespace entities
{
	HouseGenerator::HouseGenerator()
	{
		models::RawModel raw_model = render_engine::LoadObjModel("res/HouseNew.obj");
		models::ModelTexture texture = { render_engine::loader::LoadTexture("res/Texture.png") };
		texture.shine_damper = 10;
		house_model = { raw_model, texture };

		GenerateFurnitureModels();
	}

	std::deque<std::shared_ptr<Entity>> HouseGenerator::GenerateHouse(const glm::vec3& position, float y_rotation)
	{
		std::deque<std::shared_ptr<Entity>> furniture;

		// Add house
		furniture.push_front(std::make_shared<Entity>(house_model, position, glm::vec3(0, y_rotation, 0), HOUSE_SIZE));
		

		
		// Add furniture

		return furniture;
	}

	void HouseGenerator::GenerateFurnitureModels()
	{
		
	}
}
