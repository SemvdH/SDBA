#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "startup_Scene.h"

namespace scene
{
	/**
	 * deletes certain variables to prevent memory leaks
	 */
	Startup_Scene::~Startup_Scene()
	{
		std::cout << "startup scene gone!" << std::endl;
	}

	/**
	 * starts the start-up scene, calls the render and update methods in a while loop
	 */
	scene::Scenes scene::Startup_Scene::start(GLFWwindow *window)
	{
		while (return_value == scene::Scenes::STARTUP)
		{
			render();
			update(window);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		return return_value;
	}

	/**
	 * renders the models in the start-up scene
	 */
	void scene::Startup_Scene::render() 
	{

	}

	/**
	 * updates the variables for the start-up scene
	 */
	void scene::Startup_Scene::update(GLFWwindow* window)
	{

	}

	/**
	 * manages the key input in the start-up scene
	 */
	void scene::Startup_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			return_value = scene::Scenes::INGAME;
		}
	}
}
