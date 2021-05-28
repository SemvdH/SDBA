#include "startupScene.h"
#include <GLFW/glfw3.h>

void StartupScene::start()
{

}

void StartupScene::stop()
{

}

void StartupScene::render()
{

}

void StartupScene::update(GLFWwindow* window)
{

}

void StartupScene::onKey(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{
		//ideetje voor het scrollen door het menu heen
		//menuIndex = (menuIndex + 1) % 4;
	}
}
