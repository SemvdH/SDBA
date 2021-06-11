#pragma once
#include "scene.h"
#include "../gui/gui_element.h"
#include "../shaders/gui_shader.h"
#include "../model_Storage.h"

namespace scene
{
	extern GLFWwindow* window;
	

	class Loading_Scene : public scene::Scene
	{
	private:
		//return_value is an enum that is necessary for the scene switching. Whenever this changes, the scene will change to a different scene.
		scene::Scenes return_value = scene::Scenes::LOADING;
		shaders::GuiShader* gui_shader;


	private:
		void load_default_variables();
		void load_all_models();

	public:
		/**
		 * @brief Constructor of the class Loading_Scene
		 *
		 */
		Loading_Scene();

		~Loading_Scene();
		
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


