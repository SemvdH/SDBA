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
#include <deque>

#define MAX_MODEL_DEQUE_SIZE 6 // max amount of models to load at the same time
#define UPCOMING_MODEL_AMOUNT 4 // how much models should be loaded in front of us


namespace scene
{
	std::deque<entities::Entity> entites;
	std::deque<entities::Light> lights;

	models::RawModel raw_model;
	models::ModelTexture texture;
	shaders::EntityShader* shader;
	shaders::GuiShader* gui_shader;
	entities::Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	std::vector<gui::GuiTexture*> guis;

	models::TexturedModel model;


	In_Game_Scene::In_Game_Scene()
	{
		shader = new shaders::EntityShader;
		shader->Init();
		render_engine::renderer::Init(*shader);

		gui_shader = new shaders::GuiShader();
		gui_shader->Init();
	}

	void load_chunk(int model_pos)
	{
		std::cout << "loading model chunk" << std::endl;
		if (entites.size() >= MAX_MODEL_DEQUE_SIZE)
		{
			entites.pop_back();
		}
		int z_offset = model_pos * (model.raw_model.model_size.x * 20); // how much "in the distance" we should load the model
		entites.push_front(entities::Entity(model, glm::vec3(0, -50, -50 - z_offset), glm::vec3(0, 90, 0), 20));
	}


	scene::Scenes scene::In_Game_Scene::start(GLFWwindow* window)
	{
		raw_model = render_engine::LoadObjModel("res/House.obj");
		texture = { render_engine::loader::LoadTexture("res/Texture.png") };
		texture.shine_damper = 10;
		texture.reflectivity = 0;
		model = { raw_model, texture };

		/*int z = 0;

		for (int i = 0; i < 5; ++i)
		{
			entities.push_back(entities::Entity(model, glm::vec3(0, -50, -50 - z), glm::vec3(0, 90, 0), 20));
			z += (raw_model.model_size.x * 20);
		}*/
		for (int i = 0; i <= UPCOMING_MODEL_AMOUNT; i++)
		{
			load_chunk(i);
		}

		lights.push_back(entities::Light(glm::vec3(0, 1000, -7000), glm::vec3(5, 5, 5)));
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
		shader->LoadLights(lights);
		shader->LoadViewMatrix(camera);

		for (entities::Entity& model_entity : entites)
		{
			render_engine::renderer::Render(model_entity, *shader);
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
		int model_pos = -round(camera.GetPosition().z / (model.raw_model.model_size.x * 20)); // how much models we have passed, minus because we are moving in the negative z axis

		// if we have passed a model, load a new one and delete the one behind us
		if (last_model_pos != model_pos)
		{
			load_chunk(model_pos + UPCOMING_MODEL_AMOUNT);
		}
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
