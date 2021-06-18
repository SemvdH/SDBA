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

	Loading_Scene::Loading_Scene()
	{
		shader_test = new shaders::EntityShader;
		shader_test->Init();
		render_engine::renderer::Init(*shader_test);

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
		load_default_variables();
		load_all_models();
		
		int vertices = singleton::Model_Storage::get_instance()->get_house_model().raw_model.vertex_count;
		GLuint number = singleton::Model_Storage::get_instance()->get_house_model().raw_model.vao_id;

		std::cout << "check shine damper: " << singleton::Model_Storage::get_instance()->get_test_pointer()->GetModel().texture.shine_damper << std::endl;
		std::cout << "check texture id: " << singleton::Model_Storage::get_instance()->get_test_pointer()->GetModel().texture.texture_id << std::endl;

		std::cout << "" << std::endl;
		std::cout << "amount of vertices of the house model: " << vertices << std::endl;
		std::cout << "GLUint of the house model: " << number << std::endl;

		while (true) {
			render();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		return scene::Scenes::STARTUP;
	}

	void Loading_Scene::render()
	{
		render_engine::renderer::Prepare();
		//starts the shader and begins to render
		shader_test->Start();
		shader_test->LoadSkyColor(render_engine::renderer::SKY_COLOR); 
		shader_test->LoadViewMatrix(*camera_test);


		//render_engine::renderer::Render(singleton::Model_Storage::get_instance()->get_test_pointer(), *shader_test);

		/*render_engine::renderer::Prepare();
		
		gui::GuiTexture loading_image = { render_engine::loader::LoadTexture("res/loading_screen.png"),
			glm::vec2(0,0),glm::vec2(1,1) };
		
		std::vector<gui::GuiTexture*> image_list;
		image_list.push_back(&loading_image);
		
		render_engine::renderer::Render(image_list, *gui_shader);*/
		shader_test->Stop();
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
		std::cout << "raw model vertices: " << raw_model.vertex_count << std::endl;
		models::ModelTexture default_texture = { render_engine::loader::LoadTexture("res/Texture.png") };
		default_texture.shine_damper = 10;

		models::TexturedModel house = { raw_model, default_texture };
		std::cout << "house struct vertices: " << house.raw_model.vertex_count << std::endl;
		
		entities::Entity temp = entities::Entity(singleton::Model_Storage::get_instance()->get_house_model(), glm::vec3(0, -100, -500), glm::vec3(0, 90, 0), 30);

		singleton::Model_Storage::get_instance()->set_default_texture(default_texture);
		singleton::Model_Storage::get_instance()->set_house_model(house);
		singleton::Model_Storage::get_instance()->set_shared_test(&temp);
	}

	void Loading_Scene::load_all_models() 
	{

	}
}
