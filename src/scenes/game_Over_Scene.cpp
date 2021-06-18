#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "game_Over_Scene.h"
#include <iostream>
#include <opencv2/core/mat.hpp>

#include "../models/model.h"
#include "../renderEngine/loader.h"
#include "../renderEngine/obj_loader.h"
#include "../renderEngine/renderer.h"
#include "../shaders/entity_shader.h"
#include "../gui/gui_interactable.h"
#include "../toolbox/toolbox.h"
#include "../computervision/MenuTest.h"
#include "../computervision/object_detection.h"
#include "../computervision/hand_detect_region.h"
#include <opencv2/highgui.hpp>
#include "../computervision/object_detection.h"

namespace scene
{
	shaders::GuiShader* gui_shader_gameOver;
	std::vector<gui::GuiTexture*> guis_gameOver;
	std::vector<std::shared_ptr<gui::GuiTexture>> score_textures_gameOver;
	double delta_time = 0;
	double time = 0;
	bool game_over = false;

	Game_Over_Scene::Game_Over_Scene(int score) 
	{
		shaders::EntityShader shader;
		shader.Init();
		render_engine::renderer::Init(shader);
		shader.CleanUp();

		gui_shader_gameOver = new shaders::GuiShader();
		gui_shader_gameOver->Init();

		for (int i = 0; i <= 9; i++)
		{
			std::shared_ptr<gui::GuiTexture> score_pointer;

			std::string texture_path = "res/";
			texture_path += std::to_string(i);
			texture_path += ".png";

			score_pointer = std::make_unique<gui::GuiTexture>(render_engine::loader::LoadTexture(texture_path), glm::vec2(0.0f, 0.2f), glm::vec2(0.07, 0.15));

			score_textures_gameOver.push_back(score_pointer);
		}

		game_over_texture = std::make_unique<gui::GuiTexture>(render_engine::loader::LoadTexture("res/game_over.png"), glm::vec2(0.0f, 0.6f), glm::vec2(0.50f, 0.50f));
		end_score = score;
	}

	gui::Button* ConvertGuiTextureToButtonGameOver(gui::GuiTexture* texture) {
		gui::Button* button;
		if (texture != NULL)
		{
			if (texture->GetType() == gui::GuiType::BUTTON) {

				button = (gui::Button*)texture;
				return button;
			}
			else {
				button = nullptr;
				return button;
			}
		}
		else {
			button = nullptr;
			return button;
		}
	}

	scene::Scenes scene::Game_Over_Scene::start(GLFWwindow* window) {
		gui::Button button_start_scene(render_engine::loader::LoadTexture("res/Birb1.jpg"), glm::vec2(0.0f, -0.5f), glm::vec2(0.25f, 0.25f));
		button_start_scene.SetHoverTexture(render_engine::loader::LoadTexture("res/Birb2.jpg"));
		button_start_scene.SetClickedTexture(render_engine::loader::LoadTexture("res/Birb3.jpg"));
		button_start_scene.SetOnClickAction([this]()
			{
				std::cout << "Back to start screen!!" << std::endl;
				return_value = Scenes::STARTUP;
				
			});
		guis_gameOver.push_back(&button_start_scene);
	
		computervision::ObjectDetection objDetect;
		cv::Mat cameraFrame;
		gui::GuiTexture* chosen_item_gameOver = NULL; //This is the selected menu_item
		bool hand_closed = false; //Flag to prevent multiple button presses

		while (return_value == scene::Scenes:: GAMEOVER)
		{
			render();
			update(window);
			
			if (game_over) button_start_scene.ForceClick(GLFW_MOUSE_BUTTON_LEFT);
			glfwSwapBuffers(window);
			glfwPollEvents();			
		}

		gui_shader_gameOver->CleanUp();
		render_engine::loader::CleanUp();
		return return_value;
	}

	/**
	 * renders the models in the start-up scene
	 */
	void scene::Game_Over_Scene::render()
	{
		render_engine::renderer::Prepare();

		// Render GUI items
		//render_engine::renderer::Render(guis_gameOver, *gui_shader_gameOver);

		render_engine::renderer::Render(game_over_texture, *gui_shader_gameOver);
		DrawScore(end_score);
	}

	/**
	 * updates the variables for the start-up scene
	 */
	void scene::Game_Over_Scene::update(GLFWwindow* window)
	{
		for (gui::GuiTexture* button : guis_gameOver) {
			gui::Button* new_button = ConvertGuiTextureToButtonGameOver(button);
			if (new_button != NULL)
				new_button->Update(window);
		}

		UpdateDeltaTime();
		time += delta_time;

		if (time >= 5.0)
		{
			game_over = true;
		}
		

		}

	/**
	 * manages the key input in the start-up scene
	 */
	void scene::Game_Over_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			//return_value = scene::Scenes::STARTUP;
			cv::destroyWindow("camera");
		}
	}

	void Game_Over_Scene::DrawScore(int score)
	{
		std::vector<int> digits;
		score_guis_gameOver.clear();

		toolbox::GetDigitsFromNumber(score, digits);

		for (int i = digits.size() - 1; i >= 0; i--)
		{
			score_textures_gameOver[digits[i]].get()->position.x = (0.15 * i - 0.05);
			render_engine::renderer::Render(score_textures_gameOver[digits[i]], *gui_shader_gameOver);
		}
	}

	void Game_Over_Scene::UpdateDeltaTime()
	{
		double current_time = glfwGetTime();
		static double last_frame_time = current_time;
		delta_time = current_time - last_frame_time;
		last_frame_time = current_time;

	}
}