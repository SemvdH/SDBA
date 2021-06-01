#pragma once
#include <iostream>
#include <ostream>
#include <vector>
#include "scene.h"
#include "../gui/gui_interactable.h"
#include "../models/model.h"
#include "../renderEngine/loader.h"
#include "../renderEngine/obj_loader.h"
#include "../renderEngine/renderer.h"
#include "../shaders/entity_shader.h"
#include "../toolbox/toolbox.h"


namespace scene
{
	enum class Game_State
	{
		//IDLE,
		RUNNING,
		PAUSED
	};

	class In_Game_Scene : public scene::Scene
	{
	private:
		scene::Scenes return_value = scene::Scenes::INGAME;
		scene::Game_State game_state = scene::Game_State::RUNNING;

		std::vector<entities::Entity> entities_to_render;
		std::vector<entities::Light> lights;
		models::RawModel raw_model;
		models::ModelTexture texture;
		shaders::EntityShader* shader;
		shaders::GuiShader* gui_shader;
		entities::Camera *camera;
		std::vector<gui::GuiTexture*> guis;
		std::vector<gui::GuiTexture*> pause_guis;

		void render_pause_menu();
	
	public:
		In_Game_Scene();
		~In_Game_Scene();
		Scenes start(GLFWwindow* window) override;
		void render() override;
		void update(GLFWwindow* window) override;
		void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	};
}


