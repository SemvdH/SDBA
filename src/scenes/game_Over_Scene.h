#pragma once
#include "scene.h"
#include "../gui/gui_element.h"

namespace scene
{
	extern GLFWwindow* window;

	class Game_Over_Scene : public scene::Scene
	{
	private:
		
		int end_score;
		scene::Scenes return_value = scene::Scenes::GAMEOVER;
		std::vector<std::shared_ptr<gui::GuiTexture>> score_guis_gameOver;
		std::shared_ptr<gui::GuiTexture> game_over_texture;
		void UpdateDeltaTime();


	public:
		Game_Over_Scene(int score);

		Scenes start(GLFWwindow* window) override;

		void render() override;

		void update(GLFWwindow* window) override;

		void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
		/**
		* @brief: This method renders the score points onto the game window
		* @param score: Score to show
		*/
		void DrawScore(int score);
	};
}