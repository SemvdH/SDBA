#pragma once
#include "scene.h"
#include <map>

namespace scene
{
	class Startup_Scene : public scene::Scene
	{
	private:


	public:
		virtual void start() override;
		virtual void render() override;
		virtual void update() override;
		virtual void onKey(int key, int scancode, int action, int mods) override;
	};
}


