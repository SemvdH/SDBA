#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "in_Game_Scene.h"
#include "startup_Scene.h"
#include "../gui/gui_interactable.h"
#include "../models/model.h"
#include "../renderEngine/loader.h"
#include "../renderEngine/obj_loader.h"
#include "../renderEngine/renderer.h"
#include "../shaders/entity_shader.h"
#include "../toolbox/toolbox.h"


namespace scene
{
	
	In_Game_Scene::In_Game_Scene()
	{
		camera = new entities::Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

		shader = new shaders::EntityShader;
		shader->Init();	
		render_engine::renderer::Init(*shader);

		gui_shader = new shaders::GuiShader();
		gui_shader->Init();
	}

	In_Game_Scene::~In_Game_Scene()
	{
		delete camera;
		delete shader;
		delete gui_shader;
	}


	scene::Scenes scene::In_Game_Scene::start(GLFWwindow* window)
	{
		raw_model = render_engine::LoadObjModel("res/House.obj");
		texture = { render_engine::loader::LoadTexture("res/Texture.png") };
		texture.shine_damper = 10;
		texture.reflectivity = 0;
		models::TexturedModel model = { raw_model, texture };
		
		int z = 0;
		for (int i = 0; i < 5; ++i)
		{
			entities_to_render.push_back(entities::Entity(model, glm::vec3(0, -50, -50 - z), glm::vec3(0, 90, 0), 20));
			z += (raw_model.model_size.x * 20);
		}

		lights.push_back(entities::Light(glm::vec3(0, 1000, -7000), glm::vec3(5, 5, 5)));
		lights.push_back(entities::Light(glm::vec3(0, 0, -30), glm::vec3(2, 0, 2), glm::vec3(0.0001f, 0.0001f, 0.0001f)));
		lights.push_back(entities::Light(glm::vec3(0, 0, -200), glm::vec3(0, 2, 0), glm::vec3(0.0001f, 0.0001f, 0.0001f)));

		// GUI stuff
		gui::Button button(render_engine::loader::LoadTexture("res/Mayo.png"), glm::vec2(0.5f, 0.0f), glm::vec2(1, 1));
		button.SetHoverTexture(render_engine::loader::LoadTexture("res/Texture.png"));
		button.SetClickedTexture(render_engine::loader::LoadTexture("res/Mayo.png"));
		button.SetOnClickAction([]()
		{
			std::cout << "I got clicked on!" << std::endl;
		});
		guis.push_back(&button);
	

		//guis for the pause menu 
		gui::GuiTexture background(render_engine::loader::LoadTexture("res/background_grey.png"), glm::vec2(0, 0), glm::vec2(1, 1));
		pause_guis.push_back(&background);

		gui::Button pause_button_resume(render_engine::loader::LoadTexture("res/Mayo.png"), glm::vec2(0, 0), glm::vec2(0.25f, 0.25f));
		pause_button_resume.SetHoverTexture(render_engine::loader::LoadTexture("res/Texture.png"));
		pause_button_resume.SetClickedTexture(render_engine::loader::LoadTexture("res/Mayo.png"));
		pause_button_resume.SetOnClickAction([]()
			{
				std::cout << "I got clicked on the resume button!" << std::endl;
			});
		pause_guis.push_back(&pause_button_resume);

		gui::Button pause_button_quit(render_engine::loader::LoadTexture("res/Mayo.png"), glm::vec2(0.3f, 0.0f), glm::vec2(0.25f, 0.25f));
		pause_button_quit.SetHoverTexture(render_engine::loader::LoadTexture("res/Texture.png"));
		pause_button_quit.SetClickedTexture(render_engine::loader::LoadTexture("res/Mayo.png"));
		pause_button_quit.SetOnClickAction([]()
			{
				std::cout << "I got clicked on the quit button!" << std::endl;
			});
		pause_guis.push_back(&pause_button_quit);

		while (return_value == scene::Scenes::INGAME)
		{
			switch (game_state) 
			{
			/*case scene::Game_State::IDLE:
				break;*/

			case scene::Game_State::PAUSED:
				render();
				render_pause_menu();
				break;

			case scene::Game_State::RUNNING:
				update(window);
				button.Update(window);
				render();
				break;

			default:
				std::cout << "Game state unknown" << std::endl;
				break;
			}
			

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		shader->CleanUp();
		gui_shader->CleanUp();
		render_engine::loader::CleanUp();
		return return_value;
	}

	void scene::In_Game_Scene::render()
	{
		// Render
		render_engine::renderer::Prepare();

		shader->Start();
		shader->LoadSkyColor(render_engine::renderer::SKY_COLOR);
		shader->LoadLights(lights);
		shader->LoadViewMatrix(*camera);

		// Renders each entity in the entities list
		for (entities::Entity& entity : entities_to_render)
		{
			render_engine::renderer::Render(entity, *shader);
		}

		// Render GUI items
		//render_engine::renderer::Render(guis, *gui_shader);

		// Stop rendering the entities
		shader->Stop();
	}

	void scene::In_Game_Scene::update(GLFWwindow* window)
	{
		camera->Move(window);
	}

	void scene::In_Game_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			return_value = scene::Scenes::STOP;
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			game_state = scene::Game_State::PAUSED;
		}
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		{
			game_state = scene::Game_State::RUNNING;
		}
	}


	void In_Game_Scene::render_pause_menu()
	{
		render_engine::renderer::Render(pause_guis, *gui_shader);
	}
}
