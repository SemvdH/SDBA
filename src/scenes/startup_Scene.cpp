#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "startup_Scene.h"

namespace scene
{
	std::map<Scenes, Scene*> scenes;
	Scene* current_scene;
	GLFWwindow* window;

	void scene::Startup_Scene::start() 
	{

	}

	void scene::Startup_Scene::render() 
	{

	}

	void scene::Startup_Scene::update() 
	{

	}

	void scene::Startup_Scene::onKey(int key, int scancode, int action, int mods) 
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			current_scene = scenes[Scenes::INGAME];
			current_scene->start();
		}
	}
}
