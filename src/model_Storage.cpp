#include "model_Storage.h"


singleton::Model_Storage* singleton::Model_Storage::instance{nullptr};
std::mutex singleton::Model_Storage::mutex;

singleton::Model_Storage::~Model_Storage()
{
	delete instance;
}

singleton::Model_Storage* singleton::Model_Storage::get_instance()
{
	std::lock_guard<std::mutex> lock(mutex);
	if (instance == nullptr)
		instance = new Model_Storage();

	return instance;
}

/**
 * add methods
 */

void singleton::Model_Storage::add_couch(models::TexturedModel couch)
{
	couches.push_back(couch);
}

void singleton::Model_Storage::add_table(models::TexturedModel table)
{
	tables.push_back(table);
}

void singleton::Model_Storage::add_chair(models::TexturedModel chair)
{
	chairs.push_back(chair);
}

void singleton::Model_Storage::add_plant(models::TexturedModel plant)
{
	plants.push_back(plant);
}

void singleton::Model_Storage::add_guitar(models::TexturedModel guitar)
{
	guitars.push_back(guitar);
}

void singleton::Model_Storage::add_bookshelf(models::TexturedModel bookshelf)
{
	bookshelves.push_back(bookshelf);
}

void singleton::Model_Storage::add_lamp(models::TexturedModel lamp)
{
	lamps.push_back(lamp);
}

void singleton::Model_Storage::addd_ceiling_object(models::TexturedModel co)
{
	ceiling_objects.push_back(co);
}

void singleton::Model_Storage::add_misc(models::TexturedModel misc)
{
	miscs.push_back(misc);
}

/**
 * getters 
 */

std::deque<models::TexturedModel> singleton::Model_Storage::get_all_couches()
{
	return couches;
}

std::deque<models::TexturedModel> singleton::Model_Storage::get_all_tables()
{
	return tables;
}

std::deque<models::TexturedModel> singleton::Model_Storage::get_all_chairs()
{
	return chairs;
}

std::deque<models::TexturedModel> singleton::Model_Storage::get_all_plants()
{
	return plants;
}

std::deque<models::TexturedModel> singleton::Model_Storage::get_all_guitars()
{
	return guitars;
}

std::deque<models::TexturedModel> singleton::Model_Storage::get_all_bookshelves()
{
	return bookshelves;
}

std::deque<models::TexturedModel> singleton::Model_Storage::get_all_lamps()
{
	return lamps;
}

std::deque<models::TexturedModel> singleton::Model_Storage::get_all_ceiling_objects()
{
	return ceiling_objects;
}

std::deque<models::TexturedModel> singleton::Model_Storage::get_all_miscs()
{
	return miscs;
}

models::TexturedModel singleton::Model_Storage::get_couch(int index)
{
	return couches[index];
}

models::TexturedModel singleton::Model_Storage::get_table(int index)
{
	return tables[index];
}

models::TexturedModel singleton::Model_Storage::get_chair(int index)
{
	return chairs[index];
}

models::TexturedModel singleton::Model_Storage::get_plant(int index)
{
	return plants[index];
}

models::TexturedModel singleton::Model_Storage::get_guitar(int index)
{
	return guitars[index];
}

models::TexturedModel singleton::Model_Storage::get_bookshelf(int index)
{
	return bookshelves[index];
}

models::TexturedModel singleton::Model_Storage::get_lamp(int index)
{
	return lamps[index];
}

models::TexturedModel singleton::Model_Storage::get_ceiling_object(int index)
{
	return ceiling_objects[index];
}

models::TexturedModel singleton::Model_Storage::get_misc(int index)
{
	return miscs[index];
}


//getters for default variables
models::TexturedModel singleton::Model_Storage::get_house_model()
{
	return house_model;
}

models::ModelTexture singleton::Model_Storage::get_default_texture()
{
	return default_texture;
}

 //setters for deafult variables
void singleton::Model_Storage::set_house_model(models::TexturedModel house)
{
	house_model = house;
}

void singleton::Model_Storage::set_default_texture(models::ModelTexture texture)
{
	default_texture = texture;
}




void singleton::Model_Storage::set_shared_test(entities::Entity* temp)
{
	test_pointer = temp;
}

entities::Entity* singleton::Model_Storage::get_test_pointer()
{
	return test_pointer;
}




