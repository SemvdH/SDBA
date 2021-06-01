#pragma once
#include "scene.h"
#include "../gui/gui_interactable.h"

namespace scene
{
	extern GLFWwindow* window;

	class Startup_Scene : public scene::Scene
	{
	private:
		scene::Scenes return_value = scene::Scenes::STARTUP;

	public:
		Startup_Scene();
		gui::Button* ConvertGuiTextureToButton(gui::GuiTexture* texture);
		Scenes start(GLFWwindow* window) override;
		void render() override;
		void update(GLFWwindow* window) override;
		void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	};
}


