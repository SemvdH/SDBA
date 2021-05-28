#pragma once
#include "scene.h"
class StartupScene : public Scene
{
private:
	int menuIndex;

public:
	virtual void start() override;
	virtual void stop() override;
	virtual void render() override;
	virtual void update(GLFWwindow* window) override;
	virtual void onKey(int key, int scancode, int action, int mods) override;
};

