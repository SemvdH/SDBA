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
	std::vector<entities::Entity> entities;
	std::vector<entities::Light> lights;
	models::RawModel raw_model;
	models::ModelTexture texture;
	shaders::EntityShader shader;
	entities::Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

	extern GLFWwindow* window;

	
	void scene::In_Game_Scene::start() 
	{
		raw_model = render_engine::LoadObjModel("res/House.obj");
		texture = { render_engine::loader::LoadTexture("res/Texture.png") };
		texture.shine_damper = 10;
		texture.reflectivity = 0;
		models::TexturedModel model = { raw_model, texture };
		
		int z = 0;
		for (int i = 0; i < 5; ++i)
		{
			entities.push_back(entities::Entity(model, glm::vec3(0, -50, -50 - z), glm::vec3(0, 90, 0), 20));
			z += (raw_model.model_size.x * 20);
		}

		shader.Init();
		render_engine::renderer::Init(shader);

		lights.push_back(entities::Light(glm::vec3(0, 1000, -7000), glm::vec3(5, 5, 5)));
		lights.push_back(entities::Light(glm::vec3(0, 0, -30), glm::vec3(2, 0, 2), glm::vec3(0.0001f, 0.0001f, 0.0001f)));
		lights.push_back(entities::Light(glm::vec3(0, 0, -200), glm::vec3(0, 2, 0), glm::vec3(0.0001f, 0.0001f, 0.0001f)));

	}

	void scene::In_Game_Scene::render()
	{
		// Render
		render_engine::renderer::Prepare();

		shader.Start();
		shader.LoadSkyColor(render_engine::renderer::SKY_COLOR);
		shader.LoadLights(lights);
		shader.LoadViewMatrix(camera);
		// Renders each entity in the entities list
		for (entities::Entity& entity : entities)
		{
			render_engine::renderer::Render(entity, shader);
		}

		// Stop rendering the entities
		shader.Stop();
	}

	void scene::In_Game_Scene::update()
	{
		camera.Move(window);
	}

	void scene::In_Game_Scene::onKey(int key, int scancode, int action, int mods)
	{
	
	}

}
