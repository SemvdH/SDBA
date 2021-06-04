#pragma once
#include "scene.h"
#include <map>

namespace scene
{
	extern GLFWwindow* window;

	class Startup_Scene : public scene::Scene
	{
	private:
		//return_value is an enum that is necessary for the scene switching. Whenever this changes, the scene will change to a different scene.
		scene::Scenes return_value = scene::Scenes::STARTUP;

	public:
		~Startup_Scene();

		/**
		 * @brief the method start is the start of the start-up scene where a while loop runs, this runs the scene.
		 * @param window the main window of the application
		 * @return Scene value that indicates in which scene the application is
		 */
		Scenes start(GLFWwindow* window) override;

		/**
		 * @brief this method renders the models for the start-up scene
		 * @param
		 * @return void
		 */
		void render() override;

		/**
		 * @brief this method updates the models/variables for the start-up scene
		 * @param window the main window of the application
		 * @return void
		 */
		void update(GLFWwindow* window) override;

		/**
		 * @brief this method updates the models/variables for the start-up scene
		 * @param window the main window of the application
		 * @param key this is the keycode on which key has been pressed
		 * @param scancode -
		 * @param action-
		 * @param mods -
		 * @return void
		 */
		void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	};
}


