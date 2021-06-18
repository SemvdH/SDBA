#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "startup_Scene.h"
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




namespace scene
{
	shaders::GuiShader* gui_shader1;
	std::vector<gui::GuiTexture*> guis1;
  computervision::ObjectDetection objDetect;

	float item_number = 0;

	bool hand_mode = false;

	Startup_Scene::Startup_Scene() {
		shaders::EntityShader shader;
		shader.Init();
		render_engine::renderer::Init(shader);
		shader.CleanUp();

		gui_shader1 = new shaders::GuiShader();
		gui_shader1->Init();
	}

	gui::Button* ConvertGuiTextureToButton(gui::GuiTexture* texture) {
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

	/*gui::InteractableGui* ConvertGuiTextureToInteractableGui(gui::GuiTexture* texture) {
		if (texture != NULL)
			if (texture->GetType() == gui::GuiType::BUTTON) {
				return (gui::InteractableGui*)texture;
			}
			else {
				return NULL;
			}

	}*/

	gui::GuiTexture* GetMenuItem(bool hand_state) {
		if(hand_state)
		item_number += 0.20f;

		int temp_item_number = item_number;
		
		//If temp_item_number is equal to the size of the array, set item_number bac to zero to loop through the array again
		if (temp_item_number == guis1.size()) {
			item_number = 0;
			temp_item_number = 0;
		}
		std::cout << guis1[temp_item_number]->texture << std::endl;
		return guis1[temp_item_number];
	}

	scene::Scenes scene::Startup_Scene::start(GLFWwindow *window)
	{
		// GUI stuff
		gui::Button button_start(render_engine::loader::LoadTexture("res/menu_item_start1.png"), glm::vec2(0.0f, 0.6f), glm::vec2(0.25f, 0.25f));
		button_start.SetHoverTexture(render_engine::loader::LoadTexture("res/menu_item_start1_hover.png"));
		button_start.SetClickedTexture(render_engine::loader::LoadTexture("res/menu_item_start1_click.png"));
		std::function<void()> start_fun = [this]()
		{
			std::cout << "Clicked on button: Start!" << std::endl;
			return_value = scene::Scenes::INGAME;
			cv::destroyWindow("camera");

		};
		button_start.SetOnClickAction(start_fun);

		guis1.push_back(&button_start);

		gui::Button button_quit(render_engine::loader::LoadTexture("res/menu_item_quit1.png"), glm::vec2(0.0f, -0.6f), glm::vec2(0.25f, 0.25f));
		button_quit.SetHoverTexture(render_engine::loader::LoadTexture("res/menu_item_quit1_hover.png"));
		button_quit.SetClickedTexture(render_engine::loader::LoadTexture("res/menu_item_quit1_click.png"));
		std::function<void()> quit_fun = [this]()
		{
			std::cout << "Clicked on button: Quit!" << std::endl;
			return_value = scene::Scenes::STOP;
			cv::destroyWindow("camera");
		};
		button_quit.SetOnClickAction(quit_fun);
		guis1.push_back(&button_quit);

		computervision::ObjectDetection objDetect;
		cv::Mat cameraFrame;
		gui::GuiTexture* chosen_item = NULL; //This is the selected menu_item
		bool hand_closed = false; //Flag to prevent multiple button presses
		
		while (return_value == scene::Scenes::STARTUP)
		{
			render();
			update(window);
			
			if (hand_mode) {
				cameraFrame = objDetect.ReadCamera();

				//Get hand state from camera
				bool detect = false;
				bool hand_detection = objDetect.DetectHand(cameraFrame,detect);

				if (hand_detection)
				{
					hand_closed = false;
					std::cout << "hand is opened" << std::endl;

					//Loop through menu items
					chosen_item = GetMenuItem(true);

					gui::Button* new_button = ConvertGuiTextureToButton(chosen_item);
					if (new_button != NULL) {
						const float x_pos = (chosen_item->position.x + 1.0) * WINDOW_WIDTH / 2;
						const float y_pos = (1.0 - chosen_item->position.y) * WINDOW_HEIGHT / 2;

						//Set cursor to location of selected menu_item
						glfwSetCursorPos(window, x_pos, y_pos);
					}
				}
				else if (!hand_detection)
				{
					std::cout << "hand is closed" << std::endl;

					//Gets selected menu_item
					chosen_item = GetMenuItem(false);
					gui::Button* new_button = ConvertGuiTextureToButton(chosen_item);

					if (new_button != NULL && !hand_closed) {
						//Run function click
						new_button->ForceClick(GLFW_MOUSE_BUTTON_LEFT);
						hand_closed = true;
					}
				}
			}

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		gui_shader1->CleanUp();
		//render_engine::loader::CleanUp();
		return return_value;
	}

	/**
	 * renders the models in the start-up scene
	 */
	void scene::Startup_Scene::render() 
	{
		render_engine::renderer::Prepare();

		// Render GUI items
		render_engine::renderer::Render(guis1, *gui_shader1);
	}

	/**
	 * updates the variables for the start-up scene
	 */
	void scene::Startup_Scene::update(GLFWwindow* window)
	{
		for (gui::GuiTexture* button : guis1) {
			gui::Button* new_button = ConvertGuiTextureToButton(button);
			if (new_button != NULL)
				new_button->Update(window);
		}
		bool hand_present;
		objDetect.DetectHand(objDetect.ReadCamera(),hand_present);
	}

	/**
	 * manages the key input in the start-up scene
	 */
	void scene::Startup_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{

			return_value = scene::Scenes::INGAME;
			cv::destroyWindow("camera");
		}
		else if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
			hand_mode = !hand_mode;
		}
	}
}
