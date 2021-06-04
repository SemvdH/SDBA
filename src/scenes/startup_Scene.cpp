#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "startup_Scene.h"
#include "../computervision/ObjectDetection.h"

namespace scene
{
	computervision::ObjectDetection objDetect;

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
		objDetect.detectHand(objDetect.readCamera());

	}

	void scene::Startup_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			return_value = scene::Scenes::INGAME;
		}
	}
}
