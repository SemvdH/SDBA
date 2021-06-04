#include "HouseGenerator.h"

#include <functional>
#include <iostream>

#include "../renderEngine/obj_loader.h"
#include "../renderEngine/Loader.h"
#include "../toolbox/toolbox.h"

namespace entities
{
	HouseGenerator::HouseGenerator()
	{
		models::RawModel raw_model = render_engine::LoadObjModel("res/HouseNew.obj");
		default_texture = { render_engine::loader::LoadTexture("res/Texture.png") };
		default_texture.shine_damper = 10;
		house_model = { raw_model, default_texture };

		GenerateFurnitureModels();
	}

	std::deque<std::shared_ptr<Entity>> HouseGenerator::GenerateHouse(const glm::vec3& position, float y_rotation)
	{
		std::deque<std::shared_ptr<Entity>> furniture;

		// Add house
		furniture.push_front(std::make_shared<Entity>(house_model, position, glm::vec3(0, y_rotation, 0), HOUSE_SIZE));
		
		// Add furniture
		models::TexturedModel couch = GetFurnitureModel(Furniture::COUCH);		
		furniture.push_back(std::make_shared<Entity>(couch, glm::vec3(position.x, position.y + 20, position.z + 10), glm::vec3(0, 0, 0), 1));
		
		return furniture;
	}

	models::TexturedModel HouseGenerator::GetFurnitureModel(Furniture furniture)
	{
		const auto found = furniture_models.find(furniture);
		if (found == furniture_models.end())
		{
			std::cerr << "OH NEEEEEEEEEEEEEEE";
		}
		
		auto models = found->second;

		const int modelNumber = toolbox::Random(0, models.size() - 1);
		
		return models[modelNumber];
	}

	void HouseGenerator::GenerateFurnitureModels()
	{
		// Couches
		std::deque<models::TexturedModel> couches;
		
		models::RawModel couch_inside_model = render_engine::LoadObjModel("res/couchThree.obj");
		models::TexturedModel couch_inside = { couch_inside_model, default_texture };
		couches.push_back(couch_inside);
		
		furniture_models.insert(std::pair<Furniture, std::deque<models::TexturedModel>>(Furniture::COUCH, couches));
	}
}
