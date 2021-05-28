#pragma once
#include "scene.h"
class StartupScene : public Scene
{
private:
	int menuIndex;

public:
	void start() override;
	void stop() override;
	void render() override;
	void update(GLFWwindow* window) override;
	void onKey(int key, int scancode, int action, int mods) override;
};

