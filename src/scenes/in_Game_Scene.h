#pragma once
#include "scene.h"

namespace scene
{
	class In_Game_Scene : public scene::Scene
	{
	private:

	
	public:
		virtual void start() override;
		virtual void render() override;
		virtual void update() override;
		virtual void onKey(int key, int scancode, int action, int mods) override;
	};
}


