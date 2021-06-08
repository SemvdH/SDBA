#pragma once
#include "scene.h"

namespace scene
{

	class In_Game_Scene : public scene::Scene
	{
	private:
		scene::Scenes return_value = scene::Scenes::INGAME;
		void update_hand_detection();
	
	public:
		In_Game_Scene();

		Scenes start(GLFWwindow* window) override;
		void render() override;
		void update(GLFWwindow* window) override;
		void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	};
}


