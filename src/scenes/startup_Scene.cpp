#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "startup_Scene.h"

namespace scene
{
	Startup_Scene::~Startup_Scene()
	{
		std::cout << "startup scene gone!" << std::endl;
	}

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

	void scene::Startup_Scene::render() 
	{

	}

	void scene::Startup_Scene::update(GLFWwindow* window)
	{

	}

	void scene::Startup_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			return_value = scene::Scenes::INGAME;
		}
	}
}
