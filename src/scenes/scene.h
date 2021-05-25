#pragma once
#include <GLFW/glfw3.h>

class Scene
{
public:
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void render() = 0;
	virtual void update(GLFWwindow* window) = 0;
	virtual void onKey(int key, int scancode, int action, int mods) {};
};



enum class Scenes
{
	STARTUP,
	INGAME,
	GAMEOVER,
	SETTINGS,
	CALIBRATION
};
