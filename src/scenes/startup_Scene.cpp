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
#include "../computervision/ObjectDetection.h"




namespace scene
{
	shaders::GuiShader* gui_shader1;
	std::vector<gui::GuiTexture*> guis1;

	float item_number = 0;


	Startup_Scene::Startup_Scene() {
		shaders::EntityShader shader;
		shader.Init();
		render_engine::renderer::Init(shader);
		shader.CleanUp();

		gui_shader1 = new shaders::GuiShader();
		gui_shader1->Init();
	}

	gui::Button* ConvertGuiTextureToButton(gui::GuiTexture* texture) {
		if (texture != NULL)
			if (texture->GetType() == gui::GuiType::BUTTON) {
				
				gui::Button* button = (gui::Button*)texture;
				return button;
			}
			else {
				return NULL;
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
		button_start.SetOnClickAction([]()
			{
				std::cout << "Clicked on button: Start!" << std::endl;
				
			});
		guis1.push_back(&button_start);

		gui::Button button_calibrate(render_engine::loader::LoadTexture("res/menu_item_calibrate1.png"), glm::vec2(0.0f, 0.0f), glm::vec2(0.25f, 0.25f));
		button_calibrate.SetHoverTexture(render_engine::loader::LoadTexture("res/menu_item_calibrate1_hover.png"));
		button_calibrate.SetClickedTexture(render_engine::loader::LoadTexture("res/menu_item_calibrate1_click.png"));
		button_calibrate.SetOnClickAction([]()
			{
				std::cout << "Clicked on button: Calibrate!" << std::endl;

			});
		guis1.push_back(&button_calibrate);

		gui::Button button_quit(render_engine::loader::LoadTexture("res/menu_item_quit1.png"), glm::vec2(0.0f, -0.6f), glm::vec2(0.25f, 0.25f));
		button_quit.SetHoverTexture(render_engine::loader::LoadTexture("res/menu_item_quit1_hover.png"));
		button_quit.SetClickedTexture(render_engine::loader::LoadTexture("res/menu_item_quit1_click.png"));
		button_quit.SetOnClickAction([]()
			{
				std::cout << "Clicked on button: Quit!" << std::endl;
			});
		guis1.push_back(&button_quit);

		computervision::ObjectDetection objDetect;
		cv::Mat cameraFrame;
		gui::GuiTexture* chosen_item = NULL;
		bool hand_closed = false;
		
		while (return_value == scene::Scenes::STARTUP)
		{
			render();
			update(window);
			for (gui::GuiTexture* button : guis1) {
				gui::Button* new_button = ConvertGuiTextureToButton(button);
				if(new_button != NULL)
				new_button->Update(window);
			}
			
			////////////////////////// KIMS SHIT ////////////////////////////////////
			cameraFrame = objDetect.readCamera();
			//computervision::MenuTest menu_test;

			//Get hand state from camera
			bool hand_detection = objDetect.detectHand(cameraFrame);

			if (hand_detection)
			{
				hand_closed = false;

				std::cout << "hand is opened" << std::endl;

				//Loop through menu items
				chosen_item = GetMenuItem(true);

				//For debug only, to see if chosen item is selected properly when hand is opened
				std::cout << "chosen item: " << chosen_item << std::endl;

				gui::Button* new_button = ConvertGuiTextureToButton(chosen_item);
				if (new_button != NULL) {
					//Set hover texture of button selected
					const float x_pos = (chosen_item->position.x + 1.0)*WINDOW_WIDTH/2;
					const float y_pos = (1.0 - chosen_item->position.y)*WINDOW_HEIGHT/2;

					glfwSetCursorPos(window, x_pos, y_pos);
					std::cout << "Cursor pos: " << x_pos << "::" << y_pos << std::endl;
				}
			}
			else if (!hand_detection)
			{
				//for debug only, to see if the chosen item is selected properly when hand is closed
				std::cout << "hand is closed" << std::endl;
				//std::cout << "item to start: " << chosen_item << std::endl;
				/*
				//TODO link chosen item to the correct game states
				switch (chosen_item)
				{
				case 1:
					//Game state 0
					std::cout << "in case: " << chosen_item << std::endl;
					break;
				case 2:
					//Game state 1
					std::cout << "in case: " << chosen_item << std::endl;
					break;
				case 3:
					//Game state 2
					std::cout << "in case: " << chosen_item << std::endl;
					break;
				case 4:
					//Game state 3
					std::cout << "in case: " << chosen_item << std::endl;
				default:
					break;
				}
				*/
				//Click on button selected in guis1

				chosen_item = GetMenuItem(false);
				
				std::cout << chosen_item->texture << std::endl;
				gui::Button* new_button = ConvertGuiTextureToButton(chosen_item);
				if (new_button != NULL && !hand_closed) {
					//Run function click
					new_button->ForceClick(GLFW_MOUSE_BUTTON_LEFT);
					hand_closed = true;
				}
			}

			///////////////////////// END OF KIMS SHIT ///////////////////////////////

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		gui_shader1->CleanUp();
		render_engine::loader::CleanUp();
		return return_value;
	}

	void scene::Startup_Scene::render() 
	{
		render_engine::renderer::Prepare();

		// Render GUI items
		render_engine::renderer::Render(guis1, *gui_shader1);
	}

	void scene::Startup_Scene::update(GLFWwindow* window)
	{

	}

	void scene::Startup_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			return_value = scene::Scenes::INGAME;
		}
	}
}
