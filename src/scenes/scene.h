#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>


namespace scene {

	/**
	 * this enum represents the scenes in the game, those wil help to keep track in which scene the game is.
	 */
	enum class Scenes
	{
		STARTUP,
		INGAME,
		GAMEOVER,
		CALIBRATION,
		STOP
	};

	class Scene
	{		
	public:
		virtual ~Scene() = 0;
		
		/**
		 * @brief the method start is the start of a scene where a while loop runs, this runs the scene.
		 * @param window the main window of the application
		 * @return Scene value that indicates in which scene the application is
		 */
		virtual Scenes start(GLFWwindow* window) = 0;

		/**
		 * @brief this method renders the models for a scene
		 * @param
		 * @return void
		 */
		virtual void render() = 0;

		/**
		 * @brief this method updates the models/variables for a scene
		 * @param window the main window of the application
		 * @return void
		 */
		virtual void update(GLFWwindow* window) = 0;

		/**
		 * @brief this method updates the models/variables for a scene
		 * @param window the main window of the application
		 * @param key this is the keycode on which key has been pressed
		 * @param scancode -
		 * @param action-
		 * @param mods -
		 * @return void
		 */
		virtual void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {};

	};
}
