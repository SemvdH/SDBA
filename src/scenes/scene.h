#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>


namespace scene {

	

	class Scene
	{
	public:
		virtual void start() = 0;
		virtual void render() = 0;
		virtual void update() = 0;
		virtual void onKey(int key, int scancode, int action, int mods) {};

	};

	enum class Scenes
	{
		STARTUP,
		INGAME,
		GAMEOVER,
		CALIBRATION
	};

	extern std::map<Scenes, Scene*> scenes;
	extern Scene* current_scene;
	extern GLFWwindow* window;
}


