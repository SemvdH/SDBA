#pragma once
#include "scene.h"
class InGameScene : public Scene
{
private:


public:
	void start() override;
	void stop() override;
	void render() override;
	void update(GLFWwindow* window) override;
	void onKey(int key, int scancode, int action, int mods) override;

	
};

