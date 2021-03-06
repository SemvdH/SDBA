#include "loading_Scene.h"

#include <iostream>

#include "../renderEngine/Renderer.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/obj_loader.h"
#include "../gui/gui_element.h"
#include "../entities/collision_entity.h"

namespace scene
{
	std::unique_ptr<entities::Camera> camera_test;
	shaders::EntityShader* shader_test;
	std::deque<std::shared_ptr<entities::Entity>> test;

	Loading_Scene::Loading_Scene()
	{
		shader_test = new shaders::EntityShader;
		shader_test->Init();
		render_engine::renderer::Init(*shader_test);
		delete shader_test;
		
		gui_shader = new shaders::GuiShader();
		gui_shader->Init();

		camera_test = std::make_unique<entities::Camera>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

	}

	Loading_Scene::~Loading_Scene()
	{
		delete gui_shader;
	}

	Scenes Loading_Scene::start(GLFWwindow* window)
	{
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		load_default_variables();
		load_all_models();
		
		return scene::Scenes::STARTUP;
	}

	void Loading_Scene::render()
	{
		render_engine::renderer::Prepare();
		//starts the shader and begins to render
		//shader_test->Start();
		//shader_test->LoadSkyColor(render_engine::renderer::SKY_COLOR); 
		//shader_test->LoadViewMatrix(*camera_test);
				
		gui::GuiTexture loading_image = { render_engine::loader::LoadTexture("res/loading_screen.png"),
			glm::vec2(0,0),glm::vec2(1,1) };
		
		std::vector<gui::GuiTexture*> image_list;
		image_list.push_back(&loading_image);
		
		render_engine::renderer::Render(image_list, *gui_shader);
		//shader_test->Stop();

		gui_shader->CleanUp();
	}

	void Loading_Scene::update(GLFWwindow* window)
	{
	}

	
	void Loading_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
	}


	void Loading_Scene::load_default_variables()
	{
		models::RawModel raw_model = render_engine::LoadObjModel("res/HouseNew.obj");
		models::ModelTexture default_texture = { render_engine::loader::LoadTexture("res/Texture.png") };
		default_texture.shine_damper = 10;
		models::TexturedModel house = { raw_model, default_texture };
		
		singleton::Model_Storage::get_instance()->set_house_model(house);
		singleton::Model_Storage::get_instance()->set_default_texture(default_texture);
	}

	void Loading_Scene::load_all_models() 
	{
		// Couches
		singleton::Model_Storage::get_instance()->add_couch({ render_engine::LoadObjModel("res/couchThree.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_couch({ render_engine::LoadObjModel("res/Coach.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_couch({ render_engine::LoadObjModel("res/lawnBenchOne.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_furniture_model({ {singleton::FurnitureType::COUCH, 2}, singleton::Model_Storage::get_instance()->get_all_couches() });
		
		// Tables
		singleton::Model_Storage::get_instance()->add_table({ render_engine::LoadObjModel("res/tableOne.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_table({ render_engine::LoadObjModel("res/tableTwo.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_table({ render_engine::LoadObjModel("res/bureauOne.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_furniture_model({ {singleton::FurnitureType::TABLE, 2}, singleton::Model_Storage::get_instance()->get_all_tables() });

		// Chairs
		singleton::Model_Storage::get_instance()->add_chair({ render_engine::LoadObjModel("res/launchchair.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_chair({ render_engine::LoadObjModel("res/lawnChairOne.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_chair({ render_engine::LoadObjModel("res/ugly_chair.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_furniture_model({ {singleton::FurnitureType::CHAIR, 1}, singleton::Model_Storage::get_instance()->get_all_chairs() });

		// Plants
		singleton::Model_Storage::get_instance()->add_plant({ render_engine::LoadObjModel("res/plantOne.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_plant({ render_engine::LoadObjModel("res/plantTwo.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_plant({ render_engine::LoadObjModel("res/plantThree.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_furniture_model({ {singleton::FurnitureType::PLANT, 1}, singleton::Model_Storage::get_instance()->get_all_plants() });

		// Guitars
		singleton::Model_Storage::get_instance()->add_guitar({ render_engine::LoadObjModel("res/guitarOne.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_guitar({ render_engine::LoadObjModel("res/guitarTwo.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_furniture_model({ {singleton::FurnitureType::GUITAR, 1}, singleton::Model_Storage::get_instance()->get_all_guitars() });

		// Bookshelves
		singleton::Model_Storage::get_instance()->add_bookshelf({ render_engine::LoadObjModel("res/bookShelfOne.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_bookshelf({ render_engine::LoadObjModel("res/bookShelfTwo.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_bookshelf({ render_engine::LoadObjModel("res/bookShelfThree.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_furniture_model({ {singleton::FurnitureType::BOOKSHELF, 1}, singleton::Model_Storage::get_instance()->get_all_bookshelves() });

		// Lamps
		singleton::Model_Storage::get_instance()->add_lamp({ render_engine::LoadObjModel("res/lampOne.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_lamp({ render_engine::LoadObjModel("res/lampTwo.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_furniture_model({ {singleton::FurnitureType::LAMP, 1}, singleton::Model_Storage::get_instance()->get_all_lamps() });

		// Ceiling objects
		singleton::Model_Storage::get_instance()->add_ceiling_object({ render_engine::LoadObjModel("res/ceilingFan.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_ceiling_object({ render_engine::LoadObjModel("res/ceilingFanTwo.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_ceiling_object({ render_engine::LoadObjModel("res/ceilingLampOne.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_ceiling_object({ render_engine::LoadObjModel("res/ceilingLampTwo.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_furniture_model({ {singleton::FurnitureType::CEILING_OBJECTS, 1}, singleton::Model_Storage::get_instance()->get_all_ceiling_objects() });

		// Miscs
		singleton::Model_Storage::get_instance()->add_misc({ render_engine::LoadObjModel("res/tv.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_misc({ render_engine::LoadObjModel("res/radio.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_misc({ render_engine::LoadObjModel("res/Flowerpot.obj"), singleton::Model_Storage::get_instance()->get_default_texture() });
		singleton::Model_Storage::get_instance()->add_furniture_model({ {singleton::FurnitureType::MISC, 1}, singleton::Model_Storage::get_instance()->get_all_miscs() });

	}
}
