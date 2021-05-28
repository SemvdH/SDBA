#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>


namespace scene {

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
		virtual Scenes start(GLFWwindow* window) = 0;
		virtual void render() = 0;
		virtual void update(GLFWwindow* window) = 0;
		virtual void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {};

	};

	
}


