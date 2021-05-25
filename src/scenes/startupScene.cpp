#include "startupScene.h"
#include <GLFW/glfw3.h>

void start() 
{

}

void stop() 
{

}

void render() 
{

}

void update(GLFWwindow* window) 
{

}

void onKey(int key, int scancode, int action, int mods) 
{
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{
		//ideetje voor het scrollen door het menu heen
		menuIndex = (menuIndex + 1) % 4;
	}
}
