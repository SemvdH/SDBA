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
#include "../entities/HouseGenerator.h"
#include <deque>
#include <functional>
#include <memory>
#include <queue>

#define MAX_MODEL_DEQUE_SIZE 6 // max amount of models to load at the same time
#define UPCOMING_MODEL_AMOUNT 4 // how much models should be loaded in front of us


namespace scene
{
	entities::HouseGenerator* house_generator;
	std::deque<std::shared_ptr<entities::Entity>> house_models;
	std::deque<entities::Light> lights;
	std::deque<std::shared_ptr<entities::Entity>> trees;

	models::RawModel raw_model;
	models::ModelTexture texture;
	shaders::EntityShader* shader;
	shaders::GuiShader* gui_shader;
	entities::Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	std::vector<gui::GuiTexture*> guis;


	In_Game_Scene::In_Game_Scene()
	{
		shader = new shaders::EntityShader;
		shader->Init();
		render_engine::renderer::Init(*shader);

		gui_shader = new shaders::GuiShader();
		gui_shader->Init();
	}

	In_Game_Scene::~In_Game_Scene()
	{
		delete house_generator;
	}

	/**
	 * @brief loads a new chunk in front of the camera, and deletes the chunk behind the camera.
	 * 
	 * @param model_pos the amount of models the camera has passed already. This is the rounded result of (z position of camera) / (size of model)
	 * 
	 */
	void load_chunk(int model_pos)
	{
		static unsigned int furniture_count = 0;
		
		std::cout << "loading model chunk" << std::endl;
		if (house_models.size() >= MAX_MODEL_DEQUE_SIZE * furniture_count)
		{
			for (int i = 0; i < furniture_count; i++)
			{
				house_models.pop_front();
			}
		}
		int z_offset = model_pos * (house_generator->GetHouseDepth()); // how much "in the distance" we should load the model

		std::deque<std::shared_ptr<entities::Entity>> furniture = house_generator->GenerateHouse(glm::vec3(0, -75, -50 - z_offset), 90);
		furniture_count = furniture.size();
		
		house_models.insert(house_models.end(), furniture.begin(), furniture.end());
	}


	scene::Scenes scene::In_Game_Scene::start(GLFWwindow* window)
	{
		house_generator = new entities::HouseGenerator();
		// load the first few house models
		for (int i = 0; i <= UPCOMING_MODEL_AMOUNT; i++)
		{
			load_chunk(i);
		}

		lights.push_back(entities::Light(glm::vec3(0, 1000, -7000), glm::vec3(5, 5, 5))); // sun
		lights.push_back(entities::Light(glm::vec3(0, 0, -30), glm::vec3(2, 0, 2), glm::vec3(0.0001f, 0.0001f, 0.0001f)));
		lights.push_back(entities::Light(glm::vec3(0, 0, -200), glm::vec3(0, 2, 0), glm::vec3(0.0001f, 0.0001f, 0.0001f)));

		// GUI stuff
		gui::Button button(render_engine::loader::LoadTexture("res/Mayo.png"), glm::vec2(0.5f, 0.0f), glm::vec2(0.25f, 0.25f));
		button.SetHoverTexture(render_engine::loader::LoadTexture("res/Texture.png"));
		button.SetClickedTexture(render_engine::loader::LoadTexture("res/Mayo.png"));
		button.SetOnClickAction([]()
			{
				std::cout << "I got clicked on!" << std::endl;
			});
		guis.push_back(&button);


		while (return_value == scene::Scenes::INGAME)
		{
			update(window);
			button.Update(window);
			render();

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
		shader->LoadLightsDeque(lights);
		shader->LoadViewMatrix(camera);

		for (std::shared_ptr<entities::Entity> model_entity : house_models)
		{
			render_engine::renderer::Render(model_entity, *shader);
		}

		for (std::shared_ptr<entities::Entity> tree_entity : trees)
		{
			render_engine::renderer::Render(tree_entity, *shader);
		}

		// Render GUI items
		render_engine::renderer::Render(guis, *gui_shader);

		// Stop rendering the entities
		shader->Stop();
	}

	void scene::In_Game_Scene::update(GLFWwindow* window)
	{
		camera.Move(window);

		// calculate where the next house model should be loaded
		static int last_model_pos = 0;
		int model_pos = -round(camera.GetPosition().z / (house_generator->GetHouseDepth())); // how much models we have passed, minus because we are moving in the negative z axis

		// if we have passed a model, load a new one and delete the one behind us
		if (last_model_pos != model_pos)
		{
			load_chunk(model_pos + UPCOMING_MODEL_AMOUNT);
		}
		// remember the position at which the new model was added
		last_model_pos = model_pos;
	}

	void scene::In_Game_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			return_value = scene::Scenes::STOP;
		}
	}

}
