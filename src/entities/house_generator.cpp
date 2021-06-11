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

		for(int i = 0; i<toolbox::Random(1,4);i++)
		{
			FurnitureType type = FurnitureType(toolbox::Random(0, furniture_models.size() - 1));
			models::TexturedModel model = GetFurnitureModel(type);
			glm::vec3 model_pos = glm::vec3(position.x, position.y, position.z);
			collision::Box model_box = { model_pos, model.raw_model.model_size };
			model_box.SetRotation(-90);
			furniture.push_back(std::make_shared<CollisionEntity>(model, model_pos, glm::vec3(0, -90, 0), HOUSE_SIZE * 2, model_box));
		}
		
		/*
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

		models::TexturedModel plant = GetFurnitureModel(FurnitureType::PLANT);
		glm::vec3 plant_pos = glm::vec3(position.x - 50, position.y, position.z + 220);
		collision::Box plant_box = { plant_pos, plant.raw_model.model_size };
		furniture.push_back(std::make_shared<CollisionEntity>(plant, plant_pos, glm::vec3(0, 0, 0), HOUSE_SIZE, plant_box));

		models::TexturedModel guitar = GetFurnitureModel(FurnitureType::GUITAR);
		glm::vec3 guitar_pos = glm::vec3(position.x - 50, position.y, position.z + 220);
		collision::Box guitar_box = { guitar_pos, guitar.raw_model.model_size };
		furniture.push_back(std::make_shared<CollisionEntity>(guitar, guitar_pos, glm::vec3(0, 0, 0), HOUSE_SIZE, guitar_box));
		
		models::TexturedModel bookshelf = GetFurnitureModel(FurnitureType::BOOKSHELF);
		glm::vec3 bookshelf_pos = glm::vec3(position.x - 50, position.y, position.z + 220);
		collision::Box bookshelf_box = { bookshelf_pos, bookshelf.raw_model.model_size };
		furniture.push_back(std::make_shared<CollisionEntity>(bookshelf, bookshelf_pos, glm::vec3(0, 0, 0), HOUSE_SIZE, bookshelf_box));

		models::TexturedModel lamp = GetFurnitureModel(FurnitureType::LAMP);
		glm::vec3 lamp_pos = glm::vec3(position.x - 50, position.y, position.z + 220);
		collision::Box lamp_box = { lamp_pos, lamp.raw_model.model_size };
		furniture.push_back(std::make_shared<CollisionEntity>(lamp, lamp_pos, glm::vec3(0, 0, 0), HOUSE_SIZE, lamp_box));

		models::TexturedModel ceiling_object = GetFurnitureModel(FurnitureType::CEILING_OBJECTS);
		glm::vec3 ceiling_object_pos = glm::vec3(position.x - 50, position.y, position.z + 220);
		collision::Box ceiling_object_box = { ceiling_object_pos, ceiling_object.raw_model.model_size };
		furniture.push_back(std::make_shared<CollisionEntity>(ceiling_object, ceiling_object_pos, glm::vec3(0, 0, 0), HOUSE_SIZE, ceiling_object_box));

		models::TexturedModel misc = GetFurnitureModel(FurnitureType::MISC);
		glm::vec3 misc_pos = glm::vec3(position.x - 50, position.y, position.z + 220);
		collision::Box misc_box = { misc_pos, misc.raw_model.model_size };
		furniture.push_back(std::make_shared<CollisionEntity>(misc, misc_pos, glm::vec3(0, 0, 0), HOUSE_SIZE, misc_box));
		*/
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

		models::RawModel table_model3 = render_engine::LoadObjModel("res/bureauOne.obj");
		models::TexturedModel table3 = { table_model3, default_texture };
		tables.push_back(table3);
		
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

		furniture_models.insert(std::pair<FurnitureType, std::deque<models::TexturedModel>>(FurnitureType::CHAIR, chairs));


		// Plants
		std::deque<models::TexturedModel> plants;

		models::RawModel plant_model1 = render_engine::LoadObjModel("res/plantOne.obj");
		models::TexturedModel plant1 = { plant_model1, default_texture };
		plants.push_back(plant1);

		models::RawModel plant_model2 = render_engine::LoadObjModel("res/plantTwo.obj");
		models::TexturedModel plant2 = { plant_model2, default_texture };
		plants.push_back(plant2);

		models::RawModel plant_model3 = render_engine::LoadObjModel("res/plantThree.obj");
		models::TexturedModel plant3 = { plant_model3, default_texture };
		plants.push_back(plant3);
		
		furniture_models.insert(std::pair<FurnitureType, std::deque<models::TexturedModel>>(FurnitureType::PLANT, plants));

		// Guitars
		std::deque<models::TexturedModel> guitars;

		models::RawModel guitar_model1 = render_engine::LoadObjModel("res/guitarOne.obj");
		models::TexturedModel guitar1 = { guitar_model1, default_texture };
		guitars.push_back(guitar1);

		models::RawModel guitar_model2 = render_engine::LoadObjModel("res/guitarTwo.obj");
		models::TexturedModel guitar2 = { guitar_model2, default_texture };
		guitars.push_back(guitar2);
		
		furniture_models.insert(std::pair<FurnitureType, std::deque<models::TexturedModel>>(FurnitureType::GUITAR, guitars));

		// Bookshelves
		std::deque<models::TexturedModel> bookshelves;

		models::RawModel bookshelf_model1 = render_engine::LoadObjModel("res/bookShelfOne.obj");
		models::TexturedModel bookshelf1 = { bookshelf_model1, default_texture };
		bookshelves.push_back(bookshelf1);

		models::RawModel bookshelf_model2 = render_engine::LoadObjModel("res/bookShelfTwo.obj");
		models::TexturedModel bookshelf2 = { bookshelf_model2, default_texture };
		bookshelves.push_back(bookshelf2);

		models::RawModel bookshelf_model3 = render_engine::LoadObjModel("res/bookShelfThree.obj");
		models::TexturedModel bookshelf3 = { bookshelf_model3, default_texture };
		bookshelves.push_back(bookshelf3);

		furniture_models.insert(std::pair<FurnitureType, std::deque<models::TexturedModel>>(FurnitureType::BOOKSHELF, bookshelves));

		// Lamps
		std::deque<models::TexturedModel>lamps;

		models::RawModel lamp_model1 = render_engine::LoadObjModel("res/lampOne.obj");
		models::TexturedModel lamp1 = { lamp_model1, default_texture };
		lamps.push_back(lamp1);

		models::RawModel lamp_model2 = render_engine::LoadObjModel("res/lampTwo.obj");
		models::TexturedModel lamp2 = { lamp_model2, default_texture };
		lamps.push_back(lamp2);
		
		furniture_models.insert(std::pair<FurnitureType, std::deque<models::TexturedModel>>(FurnitureType::LAMP, lamps));

		// Ceiling objects
		std::deque<models::TexturedModel>ceiling_Objects;

		models::RawModel ceiling_Obj_model1 = render_engine::LoadObjModel("res/ceilingFan.obj");
		models::TexturedModel ceiling_Obj1 = { ceiling_Obj_model1, default_texture };
		ceiling_Objects.push_back(ceiling_Obj1);

		models::RawModel ceiling_Obj_model2 = render_engine::LoadObjModel("res/ceilingFanTwo.obj");
		models::TexturedModel ceiling_Obj2 = { ceiling_Obj_model2, default_texture };
		ceiling_Objects.push_back(ceiling_Obj2);

		models::RawModel ceiling_Obj_model3 = render_engine::LoadObjModel("res/ceilingLampOne.obj");
		models::TexturedModel ceiling_Obj3 = { ceiling_Obj_model3, default_texture };
		ceiling_Objects.push_back(ceiling_Obj3);

		models::RawModel ceiling_Obj_model4 = render_engine::LoadObjModel("res/ceilingLampTwo.obj");
		models::TexturedModel ceiling_Obj4 = { ceiling_Obj_model4, default_texture };
		ceiling_Objects.push_back(ceiling_Obj4);
		
		furniture_models.insert(std::pair<FurnitureType, std::deque<models::TexturedModel>>(FurnitureType::CEILING_OBJECTS, ceiling_Objects));

		// Miscs
		std::deque<models::TexturedModel> miscs;

		models::RawModel misc_model1 = render_engine::LoadObjModel("res/tv.obj");
		models::TexturedModel misc1 = { misc_model1, default_texture };
		miscs.push_back(misc1);

		models::RawModel misc_model2 = render_engine::LoadObjModel("res/radio.obj");
		models::TexturedModel misc2 = { misc_model2, default_texture };
		miscs.push_back(misc2);

		models::RawModel misc_model3 = render_engine::LoadObjModel("res/Flowerpot.obj");
		models::TexturedModel misc3 = { misc_model3, default_texture };
		miscs.push_back(misc3);

		furniture_models.insert(std::pair<FurnitureType, std::deque<models::TexturedModel>>(FurnitureType::MISC, miscs));
	}
}