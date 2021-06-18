#include "loading_Scene.h"
#include "../renderEngine/Renderer.h"
#include "../renderEngine/Loader.h"
#include "../gui/gui_element.h"

namespace scene
{
	
	Loading_Scene::Loading_Scene()
	{
		gui_shader = new shaders::GuiShader();
		gui_shader->Init();
	}

	Loading_Scene::~Loading_Scene()
	{
		delete gui_shader;
	}

	Scenes Loading_Scene::start(GLFWwindow* window)
	{
		render();
		return Scenes::STARTUP;
	}

	void Loading_Scene::render()
	{
		/*render_engine::renderer::Prepare();
		
		gui::GuiTexture loading_image = { render_engine::loader::LoadTexture("res/menu_item_start1.png"),
			glm::vec2(0,0),glm::vec2(1,1) };
		
		std::vector<gui::GuiTexture*> image_list;
		image_list.push_back(&loading_image);
		
		render_engine::renderer::Render(image_list, *gui_shader);*/
	}

	void Loading_Scene::update(GLFWwindow* window)
	{
	}

	
	void Loading_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
	}
}
