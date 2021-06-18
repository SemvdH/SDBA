#pragma once
#include <iostream>
#include <ostream>
#include <vector>
#include <memory>
#include <string>
#include <opencv2/core/base.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <deque>
#include <functional>
#include <queue>
#include <opencv2/core/base.hpp>

#include "startup_Scene.h"
#include "scene.h"
#include "../gui/gui_interactable.h"
#include "../models/model.h"
#include "../renderEngine/loader.h"
#include "../renderEngine/obj_loader.h"
#include "../renderEngine/renderer.h"
#include "../shaders/entity_shader.h"
#include "../toolbox/toolbox.h"
#include "../entities/main_character.h"
#include "../collision/collision_handler.h"
#include "../entities/house_generator.h"
#include "../computervision/hand_detect_region.h"
#include "../computervision/object_detection.h"



namespace scene
{
	/**
	* This enum is for managing the game scene state.  
	* for example: when pressed on a specific button, the game will be in a paused state and nothing about the player or the speed of the game will be updated
	* and the pause screen will show up.
	**/
	enum class Game_State
	{
		//IDLE,
		RUNNING,
		PAUSED
	};

	class In_Game_Scene : public scene::Scene
	{
	private:
		//return_value is an enum that is necessary for the scene switching. Whenever this changes, the scene will change to a different scene.
		scene::Scenes return_value = scene::Scenes::INGAME;
		//game_state is an enum that keeps track of the current game state. For example: is the game running(thus the user is playing the game) of is the game paused.
		scene::Game_State game_state = scene::Game_State::RUNNING;

		//entities_to_render is a list of entities, those entities will be rendered in the 3D environment.
		std::vector<entities::Entity> entities_to_render;
		//lights is a lost of light points in the game, for example the sun or it can be used to attach light effects to lamps.
		std::deque<entities::Light> lights;
		
		models::RawModel raw_model;
		models::ModelTexture texture;
		//the shader that is used for rendering the models.
		shaders::EntityShader* shader;
		//the gui_shader is used of rendering the gui models (for example the pause buttons).
		shaders::GuiShader* gui_shader;
		//camera is the camera view of the game scene, this camera will be behind the main character.
		std::unique_ptr<entities::Camera> camera;
		//guis is a list of all the gui components that needs to be load in the scene.
		std::vector<gui::GuiTexture*> guis;
		//pause_guis is a list of components that will be rendered when the game is paused.
		std::vector<gui::GuiTexture*> pause_guis;
		// list of gui texture that holds the textures for the score
		std::vector<std::shared_ptr<gui::GuiTexture>> score_guis;

		void UpdateDeltaTime();

		/**
		 * @brief renders the objects/gui models
		 * @param 
		 * @return void
		 */
		void render_pause_menu();

		/**
		 * @brief updates the hand detection with the deltatime and checks the hand detection for each region. als updates the camera display
		 *
		 */
		void update_hand_detection();

		/**
		 * @brief sets up the hand detection regions and sets the callbacks for the skin calibration.
		 *
		 */
		void SetupHandDetection();

		/**
		 * @brief callback that gets called when the left skin detect region timout has been reached. sets the other regions with the skin data from the first region
		 *
		 */
		void OnSkinCalibrationCallback();

		/**
		 * @brief draws the score on the screen with the digit resources.
		 * 
		 * @param score the score to display.
		 */
		void DrawScore(int score);

		/**
		 * @brief loads a new chunk in front of the camera, and deletes the chunk behind the camera.
		 *
		 * @param model_pos the amount of models the camera has passed already. This is the rounded result of (z position of camera) / (size of model)
		 *
		 */
		void LoadChunk(int model_pos);

		void update_buttons(GLFWwindow* window);

		gui::Button* ConvertGuiTextureToButton(gui::GuiTexture* texture);
	
	public:
		In_Game_Scene(int *score_ptr);
		~In_Game_Scene();

		/**
		 * @brief the method start is the start of the scene where a while loop runs, this runs the scene.
		 * @param window the main window of the application
		 * @return Scene value that indicates in which scene the application is
		 */
		Scenes start(GLFWwindow* window) override;

		/**
		 * @brief this method renders the models for the game scene
		 * @param 
		 * @return void
		 */
		void render() override;

		/**
		 * @brief this method updates the models/variables for the game scene
		 * @param window the main window of the application
		 * @return void
		 */
		void update(GLFWwindow* window) override;

		/**
		 * @brief this method updates the models/variables for the game scene
		 * @param window the main window of the application
		 * @param key this is the keycode on which key has been pressed 
		 * @param scancode -
		 * @param action-
		 * @param mods -
		 * @return void
		 */
		void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	};
}


