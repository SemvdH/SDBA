#include "house_generator.h"

#include <functional>
#include <iostream>

#include "../renderEngine/obj_loader.h"
#include "../renderEngine/Loader.h"
#include "../toolbox/toolbox.h"
#include "collision_entity.h"

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
		models::TexturedModel couch = GetFurnitureModel(FurnitureType::COUCH);
		glm::vec3 couch_pos = glm::vec3(position.x + 200, position.y, position.z + 10);
		collision::Box couch_box = { couch_pos, couch.raw_model.model_size };
		couch_box.SetRotation(-90);
		furniture.push_back(std::make_shared<CollisionEntity>(couch, couch_pos, glm::vec3(0, -90, 0), HOUSE_SIZE * 2, couch_box));

		models::TexturedModel table = GetFurnitureModel(FurnitureType::TABLE);
		glm::vec3 table_pos = glm::vec3(position.x - 30, position.y, position.z);
		collision::Box table_box = { table_pos, table.raw_model.model_size };
		furniture.push_back(std::make_shared<CollisionEntity>(table, table_pos, glm::vec3(0, 0, 0), HOUSE_SIZE * 1.3, table_box));

		models::TexturedModel chair = GetFurnitureModel(FurnitureType::CHAIR);
		glm::vec3 chair_pos = glm::vec3(position.x - 50, position.y, position.z + 220);
		collision::Box chair_box = { chair_pos, chair.raw_model.model_size };
		furniture.push_back(std::make_shared<CollisionEntity>(chair, chair_pos, glm::vec3(0, 0, 0), HOUSE_SIZE, chair_box));
		
		return furniture;
	}

	models::TexturedModel HouseGenerator::GetFurnitureModel(FurnitureType furniture)
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

		models::RawModel couch_inside_model2 = render_engine::LoadObjModel("res/Coach.obj");
		models::TexturedModel couch_inside2 = { couch_inside_model2, default_texture };
		couches.push_back(couch_inside2);

		models::RawModel couch_inside_model3 = render_engine::LoadObjModel("res/lawnBenchOne.obj");
		models::TexturedModel couch_inside3 = { couch_inside_model3, default_texture };
		couches.push_back(couch_inside3);
		
		furniture_models.insert(std::pair<FurnitureType, std::deque<models::TexturedModel>>(FurnitureType::COUCH, couches));

		// Tables
		std::deque<models::TexturedModel> tables;

		models::RawModel table_model1 = render_engine::LoadObjModel("res/tableOne.obj");
		models::TexturedModel table1 = { table_model1, default_texture };
		tables.push_back(table1);

		models::RawModel table_model2 = render_engine::LoadObjModel("res/tableTwo.obj");
		models::TexturedModel table2 = { table_model2, default_texture };
		tables.push_back(table2);
		
		furniture_models.insert(std::pair<FurnitureType, std::deque<models::TexturedModel>>(FurnitureType::TABLE, tables));

		// Chairs
		std::deque<models::TexturedModel> chairs;

		models::RawModel chair_model1 = render_engine::LoadObjModel("res/launchchair.obj");
		models::TexturedModel chair1 = { chair_model1, default_texture };
		chairs.push_back(chair1);

		models::RawModel chair_model2 = render_engine::LoadObjModel("res/lawnChairOne.obj");
		models::TexturedModel chair2 = { chair_model2, default_texture };
		chairs.push_back(chair2);

		models::RawModel chair_model3 = render_engine::LoadObjModel("res/ugly_chair.obj");
		models::TexturedModel chair3 = { chair_model3, default_texture };
		chairs.push_back(chair3);

		// Plants

		furniture_models.insert(std::pair<FurnitureType, std::deque<models::TexturedModel>>(FurnitureType::CHAIR, chairs));
	}
}
