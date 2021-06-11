#pragma once
#include "scene.h"
#include "../gui/gui_element.h"

namespace scene
{
	extern GLFWwindow* window;

	class Game_Over_Scene : public scene::Scene
	{
	private:
		scene::Scenes return_value = scene::Scenes::GAMEOVER;

	public:
		Game_Over_Scene();

		Scenes start(GLFWwindow* window) override;

		void render() override;

		void update(GLFWwindow* window) override;

		void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;

	};
}