#pragma once
#include "scene.h"
#include "../gui/gui_element.h"

namespace scene
{
	extern GLFWwindow* window;

	class Startup_Scene : public scene::Scene
	{
	private:
		//return_value is an enum that is necessary for the scene switching. Whenever this changes, the scene will change to a different scene.
		scene::Scenes return_value = scene::Scenes::STARTUP;
		void EnableHandMode();

	public:
		/**
		 * @brief Constructor of the class Startup_Scene
		 * 
		 */
		Startup_Scene();

		/**
		 * @brief 
		 * 
		 * @param window
		 * @return 
		 */
		Scenes start(GLFWwindow* window) override;

		/**
		 * @brief 
		 * 
		 */
		void render() override;

		/**
		 * @brief This method updates all the components on the window
		 * 
		 * @param window Window it updates
		 */
		void update(GLFWwindow* window) override;

		/**
		 * @brief Listener for key events
		 * 
		 * @param window Window it listens to for key events
		 * @param key Key of event that is activated
		 * @param scancode Code of Key
		 * @param action 
		 * @param mods
		 */
		void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	};
}


