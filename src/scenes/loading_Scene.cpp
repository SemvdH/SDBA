#include "loading_Scene.h"

#include <iostream>

#include "../renderEngine/Renderer.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/obj_loader.h"
#include "../gui/gui_element.h"

namespace scene
{
	Loading_Scene::Loading_Scene()
	{
		gui_shader = new shaders::GuiShader();
		gui_shader->Init();
	}

	Loading_Scene::~Loading_Scene()
	{
		delete gui_shader;
	}

	Scenes Loading_Scene::start(GLFWwindow* window)
	{
		render();
		load_default_variables();
		load_all_models();
		
		int vertices = singleton::Model_Storage::get_instance()->get_house_model().raw_model.vertex_count;
		GLuint number = singleton::Model_Storage::get_instance()->get_house_model().raw_model.vao_id;

		std::cout << "amount of vertices of the house model: " << vertices << std::endl;
		std::cout << "GLUint of the house model: " << number << std::endl;

		while (true) {

		}
		return scene::Scenes::STARTUP;
	}

	void Loading_Scene::render()
	{
		render_engine::renderer::Prepare();
		
		gui::GuiTexture loading_image = { render_engine::loader::LoadTexture("res/loading_screen.png"),
			glm::vec2(0,0),glm::vec2(1,1) };
		
		std::vector<gui::GuiTexture*> image_list;
		image_list.push_back(&loading_image);
		
		render_engine::renderer::Render(image_list, *gui_shader);
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

		singleton::Model_Storage::get_instance()->set_default_texture(default_texture);
		singleton::Model_Storage::get_instance()->set_house_model(house);
	}

	void Loading_Scene::load_all_models() 
	{

	}
}
