#pragma once
#include <iostream>
#include <deque>
#include <mutex>
#include "models/Model.h"
#include "entities/Entity.h"

namespace singleton {
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
	
	class Model_Storage
	{
	private:
		static Model_Storage* instance;
		static std::mutex mutex;

		//model of the house
		models::TexturedModel house_model;
		//default texture
		models::ModelTexture default_texture;

		//list that sorts furniture_models on type
		std::deque<FurnitureModel> furniture_models;
		
		//list of furniture:
		//couches
		std::deque<models::TexturedModel> couches;

		//tables
		std::deque<models::TexturedModel> tables;

		//chairs
		std::deque<models::TexturedModel> chairs;

		//plants
		std::deque<models::TexturedModel> plants;

		//guitars
		std::deque<models::TexturedModel> guitars;

		//bookshelves
		std::deque<models::TexturedModel> bookshelves;

		//lamps
		std::deque<models::TexturedModel>lamps;

		//ceiling objects 
		std::deque<models::TexturedModel>ceiling_objects;

		//misc
		std::deque<models::TexturedModel> miscs;

	protected:
		Model_Storage() { std::cout << "MAKING A NEW SINGLETON!!!" << std::endl; }
		~Model_Storage();

	public:
		Model_Storage(Model_Storage& other) = delete;
		void operator=(const Model_Storage&) = delete;

		static Model_Storage* get_instance();

		//some methods to execute on its instance:
		void add_couch(models::TexturedModel couch);
		void add_table(models::TexturedModel table);
		void add_chair(models::TexturedModel chair);
		void add_plant(models::TexturedModel plant);
		void add_guitar(models::TexturedModel guitar);
		void add_bookshelf(models::TexturedModel bookshelf);
		void add_lamp(models::TexturedModel lamp);
		void add_ceiling_object(models::TexturedModel co);
		void add_misc(models::TexturedModel misc);
		void add_furniture_model(FurnitureModel model);

		//getters for the whole list
		std::deque<models::TexturedModel> get_all_couches();
		std::deque<models::TexturedModel> get_all_tables();
		std::deque<models::TexturedModel> get_all_chairs();
		std::deque<models::TexturedModel> get_all_plants();
		std::deque<models::TexturedModel> get_all_guitars();
		std::deque<models::TexturedModel> get_all_bookshelves();
		std::deque<models::TexturedModel> get_all_lamps();
		std::deque<models::TexturedModel> get_all_ceiling_objects();
		std::deque<models::TexturedModel> get_all_miscs();
		std::deque<FurnitureModel> get_all_furniture_models();

		//getters for one model
		models::TexturedModel get_couch(int index);
		models::TexturedModel get_table(int index);
		models::TexturedModel get_chair(int index);
		models::TexturedModel get_plant(int index);
		models::TexturedModel get_guitar(int index);
		models::TexturedModel get_bookshelf(int index);
		models::TexturedModel get_lamp(int index);
		models::TexturedModel get_ceiling_object(int index);
		models::TexturedModel get_misc(int index);
		FurnitureModel get_furniture_model(int index);

		//getters for the standard variables
		models::TexturedModel get_house_model();
		models::ModelTexture get_default_texture();

		//setters for the standard variables
		void set_house_model(models::TexturedModel house);
		void set_default_texture(models::ModelTexture texture);

	};
}


