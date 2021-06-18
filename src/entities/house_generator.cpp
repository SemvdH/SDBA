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
	}

	void HouseGenerator::GetRandomFurniturePiece(singleton::FurniturePiece* furniture_piece)
	{
		singleton::FurnitureType random_type = singleton::FurnitureType::CEILING_OBJECTS;
		std::deque<singleton::FurnitureModel> furniture_models = singleton::Model_Storage::get_instance()->get_all_furniture_models();
		
		while (random_type == singleton::FurnitureType::CEILING_OBJECTS ) {
			random_type = singleton::FurnitureType(toolbox::Random(0, furniture_models.size() - 1));
		}

		for (auto it = furniture_models.begin(); it != furniture_models.end(); ++it)
		{
			if (it->furniture.type == random_type)
			{
				furniture_piece->type = it->furniture.type;
				furniture_piece->size = it->furniture.size;
				break;
			}
		}
		
	}

	void HouseGenerator::GetFurniturePiece(singleton::FurnitureType type, singleton::FurniturePiece* furniture_piece)
	{
		std::deque<singleton::FurnitureModel> furniture_models = singleton::Model_Storage::get_instance()->get_all_furniture_models();
		for (auto it = furniture_models.begin(); it != furniture_models.end(); ++it)
		{
			if (it->furniture.type == type)
			{
				furniture_piece->type = it->furniture.type;
				furniture_piece->size = it->furniture.size;
				break;
			}
		}
	}

	void HouseGenerator::GenerateHouse(std::deque<std::shared_ptr<Entity>>* furniture_list , const glm::vec3& position, float y_rotation)
	{
		std::deque<std::shared_ptr<Entity>> furniture;

		// Add house
		furniture_list->push_front(std::make_shared<Entity>(singleton::Model_Storage::get_instance()->get_house_model(), position, glm::vec3(0, y_rotation, 0), HOUSE_SIZE));
		int house_size_x = singleton::Model_Storage::get_instance()->get_house_model().raw_model.model_size.x * HOUSE_SIZE;
		int house_size_y = singleton::Model_Storage::get_instance()->get_house_model().raw_model.model_size.x * HOUSE_SIZE;
		int house_size_z = singleton::Model_Storage::get_instance()->get_house_model().raw_model.model_size.x * HOUSE_SIZE;

		int offset_x = singleton::Model_Storage::get_instance()->get_house_model().raw_model.model_size.z * (HOUSE_SIZE / 2);
		int offset_z = singleton::Model_Storage::get_instance()->get_house_model().raw_model.model_size.x * (HOUSE_SIZE / 2);
		double multiplier_x = house_size_x / 4;
		double multiplier_z = house_size_z / 3;

		for (int z = 1; z < 4; z++) {
			for (int x = 1; x < 4; x++)
			{
				//if (toolbox::Random(0, 100) < 90) {
				singleton::FurniturePiece furniture_piece;
				GetRandomFurniturePiece(&furniture_piece);
				if (furniture_piece.type != singleton::FurnitureType::CEILING_OBJECTS) {
					std::cout << "Furniture Piece: " << int(furniture_piece.type) << std::endl;
					models::TexturedModel model = GetFurnitureModel(&furniture_piece);
					//if (!(furniture_piece->size > 1 && x > 1)) {
					glm::vec3 model_pos = glm::vec3(position.x + (x * multiplier_x) - (multiplier_x / 2) - offset_x, position.y, position.z + (z * multiplier_z) - (multiplier_z / 2) + offset_z);

					collision::Box model_box = { model_pos, model.raw_model.model_size };
					model_box.SetRotation(-90);
					furniture_list->push_back(std::make_shared<CollisionEntity>(model, model_pos, glm::vec3(0, -90, 0), HOUSE_SIZE, model_box));
				}
				//}
			//}
			}
		}

		singleton::FurniturePiece furniture_piece;
		GetFurniturePiece(singleton::FurnitureType::CEILING_OBJECTS, &furniture_piece);
		models::TexturedModel model = GetFurnitureModel(&furniture_piece);
		glm::vec3 model_pos = glm::vec3(position.x, position.y + (house_size_y / 5 * 3), position.z);
		collision::Box model_box = { model_pos, model.raw_model.model_size };
		model_box.SetRotation(-90);
		furniture_list->push_back(std::make_shared<CollisionEntity>(model, model_pos, glm::vec3(0, -90, 0), HOUSE_SIZE, model_box));

	}

	models::TexturedModel HouseGenerator::GetFurnitureModel(const singleton::FurniturePiece* furniture)
	{
		std::deque<models::TexturedModel> furniture_list;
		std::deque<singleton::FurnitureModel> furniture_models = singleton::Model_Storage::get_instance()->get_all_furniture_models();

		std::cout << "type of furniture_piece: " << int(furniture->type) << std::endl;

		for (auto it = furniture_models.begin(); it != furniture_models.end(); ++it)
		{
			if (it->furniture.type == furniture->type)
			{
				std::deque<models::TexturedModel> textures = it->texture;
				for (int i = 0; i< textures.size(); i++)
				{
					furniture_list.push_back(textures.at(i));
				}
				std::cout << "Size of textures: " << textures.size() << std::endl;
				std::cout << "Size of furniture_list: " << furniture_list.size() << std::endl;
				break;
			}
		}
		std::cout << "Size of furniture_list after for loop: " << furniture_list.size() << std::endl;
		if (furniture_list.empty())
		{
			std::cerr << "OH NEEEEEEEEEEEEEEE";
		}

		const int modelNumber = toolbox::Random(0, furniture_list.size() - 1);

		return furniture_list.at(modelNumber);
	}
	
}
