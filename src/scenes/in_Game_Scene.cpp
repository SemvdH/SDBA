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
#include <opencv2/core/base.hpp>
#include "../computervision/HandDetectRegion.h"
#include "../computervision/ObjectDetection.h"


namespace scene
{
	std::vector<entities::Entity> entities;
	std::vector<entities::Light> lights;
	models::RawModel raw_model;
	models::ModelTexture texture;
	shaders::EntityShader *shader;
	shaders::GuiShader *gui_shader;
	entities::Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	std::vector<gui::GuiTexture*> guis;


	std::vector<computervision::HandDetectRegion> regions;
	computervision::HandDetectRegion reg_left("left", 0, 0, 150, 150), reg_right("right", 0, 0, 150, 150), reg_up("up", 0, 0, 150, 150);

	
	In_Game_Scene::In_Game_Scene()
	{
		shader = new shaders::EntityShader;
		shader->Init();	
		render_engine::renderer::Init(*shader);

		gui_shader = new shaders::GuiShader();
		gui_shader->Init();
	}

	scene::Scenes scene::In_Game_Scene::start(GLFWwindow* window)
	{
		// set up squares according to size of camera input
		cv::Mat camera_frame;
		static_camera::getCap().read(camera_frame); // get camera frame to know the width and heigth
		reg_left.SetXPos(10);
		reg_left.SetYPos(camera_frame.rows / 2 - reg_left.GetHeight()/2);
		reg_right.SetXPos(camera_frame.cols - 10 - reg_right.GetWidth());
		reg_right.SetYPos(camera_frame.rows / 2 - reg_right.GetHeight()/2);
		reg_up.SetXPos(camera_frame.cols / 2 - reg_up.GetWidth() / 2);
		reg_up.SetYPos(10);


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

		// Renders each entity in the entities list
		for (entities::Entity& entity : entities)
		{
			render_engine::renderer::Render(entity, *shader);
		}

		// Render GUI items
		render_engine::renderer::Render(guis, *gui_shader);

		// Stop rendering the entities
		shader->Stop();
	}

	void scene::In_Game_Scene::update(GLFWwindow* window)
	{
		camera.Move(window);
		update_hand_detection();
	}

	void scene::In_Game_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			cv::destroyWindow("camera");
			return_value = scene::Scenes::STOP;
		}

		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			reg_left.CalibrateBackground();
			reg_right.CalibrateBackground();
			reg_up.CalibrateBackground();
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			std::vector<int> tresholds = reg_left.CalculateSkinTresholds();
			reg_right.setSkinTresholds(tresholds);
			reg_up.setSkinTresholds(tresholds);
		}
	}

	void scene::In_Game_Scene::update_hand_detection()
	{
		cv::Mat camera_frame;
		static_camera::getCap().read(camera_frame);
		reg_left.DetectHand(camera_frame);
		reg_right.DetectHand(camera_frame);
		reg_up.DetectHand(camera_frame);

		cv::imshow("camera", camera_frame);
	}
}
