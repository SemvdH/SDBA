#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "startup_Scene.h"
#include <iostream>
#include "../models/model.h"
#include "../renderEngine/loader.h"
#include "../renderEngine/obj_loader.h"
#include "../renderEngine/renderer.h"
#include "../shaders/entity_shader.h"
#include "../gui/gui_interactable.h"
#include "../toolbox/toolbox.h"



namespace scene
{
	shaders::GuiShader* gui_shader1;
	std::vector<gui::GuiTexture*> guis1;

	Startup_Scene::Startup_Scene() {
		shaders::EntityShader shader;
		shader.Init();
		render_engine::renderer::Init(shader);
		shader.CleanUp();

		gui_shader1 = new shaders::GuiShader();
		gui_shader1->Init();
	}

	gui::Button* ConvertGuiTextureToButton(gui::GuiTexture* texture) {
		if (texture->GetType() == gui::GuiType::BUTTON) {
			return (gui::Button*)texture;
		}
		else {
			return NULL;
		}
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

		while (return_value == scene::Scenes::STARTUP)
		{
			render();
			update(window);
			for (gui::GuiTexture* button : guis1) {
				gui::Button* new_button = ConvertGuiTextureToButton(button);
				if(new_button != NULL)
				new_button->Update(window);
			}
			
	
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
