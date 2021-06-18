#include "in_Game_Scene.h"

#define MAX_MODEL_DEQUE_SIZE 6 // max amount of models to load at the same time
#define UPCOMING_MODEL_AMOUNT 4 // how much models should be loaded in front of us


namespace scene
{
	std::shared_ptr<entities::MainCharacter>main_character;
	std::deque<std::shared_ptr<entities::CollisionEntity>> collision_entities;

	//std::deque<std::shared_ptr<entities::CollisionEntity>> furniture_collision;

	entities::HouseGenerator* house_generator;
	std::deque<std::shared_ptr<entities::Entity>> house_models;

	models::RawModel raw_model, raw_model_char;
	models::ModelTexture texture;
	shaders::EntityShader* shader;
	shaders::GuiShader* gui_shader;
	std::vector<gui::GuiTexture*> guis;
	std::vector<std::shared_ptr<gui::GuiTexture>> score_textures;

	int furniture_count_old;
	int score;
	int* ptr;
	bool calibrated = false;

	float delta_time = 0;

	std::vector<computervision::HandDetectRegion*> regions;
	computervision::HandDetectRegion reg_left("left", 0, 0, 150, 150), reg_right("right", 0, 0, 150, 150), reg_up("up", 0, 0, 150, 150);

	/**
	 * sets up the first things when the objects has been made
	 */
	In_Game_Scene::In_Game_Scene(int *score_ptr)
	{
		ptr = score_ptr;
		camera = std::make_unique<entities::Camera>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

		shader = new shaders::EntityShader;
		shader->Init();
		render_engine::renderer::Init(*shader);

		gui_shader = new shaders::GuiShader();
		gui_shader->Init();
		score = 0;

		for (int i = 0; i <= 9; i++)
		{
			std::shared_ptr<gui::GuiTexture> score_pointer;

			std::string texture_path = "res/";
			texture_path += std::to_string(i);
			texture_path += ".png";

			score_pointer = std::make_unique<gui::GuiTexture>(render_engine::loader::LoadTexture(texture_path), glm::vec2(-0.9f, 0.8f), glm::vec2(0.07, 0.15));
			score_textures.push_back(score_pointer);
		}
	}

	/**
	 * temporary?
	 * just to make some bounding boxes
	 */
	collision::Box create_bounding_box(glm::vec3 size, glm::vec3 pos, int scale) {
		collision::Box box = collision::Box();
		box.size.x = size.z * scale;
		box.size.y = size.y * scale;
		box.size.z = size.x * scale;
		box.center_pos = pos;
		return box;
	}
	/**
	 * deletes certain veriables when the object will be deleted, prevents memory leaks
	 */
	In_Game_Scene::~In_Game_Scene()
	{
		delete shader;
		delete gui_shader;
		delete house_generator;
	}

	
	void In_Game_Scene::SetupHandDetection()
	{
		// set up squares according to size of camera input
		cv::Mat camera_frame;
		static_camera::getCap().read(camera_frame); // get camera frame to know the width and heigth

		reg_left.SetMainSkinDetecRegion(true);
		reg_right.SetMainSkinDetecRegion(false);
		reg_right.SetMainSkinDetecRegion(false);
		std::function<void()> callback = [this]() {OnSkinCalibrationCallback(); };
		reg_left.SetSkinTimerCallback(callback);

		reg_left.SetXPos(10);
		reg_left.SetYPos(camera_frame.rows / 2 - reg_left.GetHeight() / 2);
		reg_right.SetXPos(camera_frame.cols - 10 - reg_right.GetWidth());
		reg_right.SetYPos(camera_frame.rows / 2 - reg_right.GetHeight() / 2);
		reg_up.SetXPos(camera_frame.cols / 2 - reg_up.GetWidth() / 2);
		reg_up.SetYPos(10);
	}

	
	void In_Game_Scene::LoadChunk(int model_pos)
	{
		static unsigned int furniture_count = 0;
		std::cout << "loading model chunk" << std::endl;
		if (house_models.size() >= MAX_MODEL_DEQUE_SIZE * furniture_count)
		{
			for (int i = 0; i < furniture_count; i++)
			{
				house_models.pop_front();
				collision_entities.pop_front();
			}
		}
		int z_offset = model_pos * (house_generator->GetHouseDepth()); // how much "in the distance" we should load the model

		std::deque<std::shared_ptr<entities::CollisionEntity>> furniture;
		house_generator->GenerateHouse(&furniture, glm::vec3(0, -75, -50 - z_offset), 90);
		furniture_count = furniture.size();
		
		house_models.insert(house_models.end(), furniture.begin(), furniture.end());
		collision_entities.insert(collision_entities.end(), furniture.begin(), furniture.end());
		std::cout << "funriture_count in load chunk (house included): " << furniture_count << std::endl;
		furniture_count_old = furniture_count - 1;

	}

	/**
	 * starts the game scene, calls the render and update methods in a while loop
	 */
	scene::Scenes scene::In_Game_Scene::start(GLFWwindow* window)
	{
		texture = { render_engine::loader::LoadTexture("res/Texture.png") };
		texture.shine_damper = 10;
		texture.reflectivity = 0;


		raw_model_char = render_engine::LoadObjModel("res/beeTwo.obj");
		models::TexturedModel model_char = { raw_model_char, texture };
		collision::Box char_box = create_bounding_box(raw_model_char.model_size, glm::vec3(0, 0, 0), 1);
		main_character = std::make_shared<entities::MainCharacter>(model_char, glm::vec3(0, 50, -100), glm::vec3(0, 90, 0), 5, char_box);
		
		//collision_entities.push_back(main_character);
		house_generator = new entities::HouseGenerator();

		SetupHandDetection();

		// load the first few house models
		for (int i = 0; i <= UPCOMING_MODEL_AMOUNT; i++)
		{
			LoadChunk(i);
		}

		lights.push_back(entities::Light(glm::vec3(0, 1000, 7000), glm::vec3(5, 5, 5))); // sun
		lights.push_back(entities::Light(glm::vec3(0, 0, -30), glm::vec3(2, 0, 2), glm::vec3(0.0001f, 0.0001f, 0.0001f)));
		lights.push_back(entities::Light(glm::vec3(0, 0, -200), glm::vec3(0, 2, 0), glm::vec3(0.0001f, 0.0001f, 0.0001f)));

		// GUI stuff
		gui::Button button(render_engine::loader::LoadTexture("res/Mayo.png"), glm::vec2(0.5f, 0.0f), glm::vec2(1, 1));
		button.SetHoverTexture(render_engine::loader::LoadTexture("res/Texture.png"));
		button.SetClickedTexture(render_engine::loader::LoadTexture("res/Mayo.png"));
		button.SetOnClickAction([]()
			{
				std::cout << "I got clicked on!" << std::endl;
			});
		guis.push_back(&button);


		//guis for the pause menu 
		gui::GuiTexture background(render_engine::loader::LoadTexture("res/background_grey.png"), glm::vec2(0, 0), glm::vec2(1, 1));
		pause_guis.push_back(&background);

		gui::Button pause_button_resume(render_engine::loader::LoadTexture("res/menu_item_start1.png"), glm::vec2(0.0f, 0.3f), glm::vec2(0.25f, 0.25f));
		pause_button_resume.SetHoverTexture(render_engine::loader::LoadTexture("res/menu_item_start1_hover.png"));
		pause_button_resume.SetClickedTexture(render_engine::loader::LoadTexture("res/menu_item_start1_click.png"));
		pause_button_resume.SetOnClickAction([]()
			{
				std::cout << "I got clicked on the resume button!" << std::endl;
				//game_state = scene::Game_State::RUNNING;
			});
		pause_guis.push_back(&pause_button_resume);

		gui::Button pause_button_quit(render_engine::loader::LoadTexture("res/menu_item_quit1.png"), glm::vec2(0.0f, -0.3f), glm::vec2(0.25f, 0.25f));
		pause_button_quit.SetHoverTexture(render_engine::loader::LoadTexture("res/menu_item_quit1_hover.png"));
		pause_button_quit.SetClickedTexture(render_engine::loader::LoadTexture("res/menu_item_quit1_click.png"));
		pause_button_quit.SetOnClickAction([]()
			{
				std::cout << "I got clicked on the quit button!" << std::endl;
				//return_value = scene::Scenes::STOP;
			});
		pause_guis.push_back(&pause_button_quit);

		regions.push_back(&reg_left);
		regions.push_back(&reg_up);
		regions.push_back(&reg_right);

		//the scene loop, this while loop represent the scene
		while (return_value == scene::Scenes::INGAME)
		{
			//checks the current game state, so it can render the correct models for each state
			switch (game_state)
			{
				/*case scene::Game_State::IDLE:
					break;*/

			case scene::Game_State::PAUSED:
				render();
				render_pause_menu();
				break;

			case scene::Game_State::RUNNING:
				update(window);
				button.Update(window);
				render();
				break;

			default:
				std::cout << "Game state unknown" << std::endl;
				break;
			}


			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		shader->CleanUp();
		gui_shader->CleanUp();
		//render_engine::loader::CleanUp();
		return return_value;
	}

	/**
	 * renders the game models
	 */
	void scene::In_Game_Scene::render()
	{
		// Render
		render_engine::renderer::Prepare();
		//starts the shader and begins to render
		shader->Start();
		shader->LoadSkyColor(render_engine::renderer::SKY_COLOR);
		shader->LoadLightsDeque(lights);
		shader->LoadViewMatrix(*camera);

		for (std::shared_ptr<entities::Entity> model_entity : house_models)
		{
			render_engine::renderer::Render(model_entity, *shader);
		}

		render_engine::renderer::Render(main_character, *shader);

		// Render GUI items
		//render_engine::renderer::Render(guis, *gui_shader);

		// Stop rendering the entities
		shader->Stop();

		DrawScore(score);
	}

	//updates certain variables 
	void scene::In_Game_Scene::update(GLFWwindow* window)
	{
		UpdateDeltaTime();
		//camera.Move(window);
		update_hand_detection();
		if (!calibrated) return;
		main_character->Move(regions);
		if (!main_character.get()->GetOnCollide())
		{	
			*ptr = score;
			std::cout << "Score: " << score << std::endl;
			return_value = scene::Scenes::GAMEOVER;
		}

		camera->Follow(main_character->GetPosition());

		// calculate where the next house model should be loaded
		static int last_model_pos = 0;
		int model_pos = -round(camera->GetPosition().z / (house_generator->GetHouseDepth())); // how much models we have passed, minus because we are moving in the negative z axis

		// if we have passed a model, load a new one and delete the one behind us
		if (last_model_pos != model_pos)
		{
			std::cout << "updating score" << std::endl;
			LoadChunk(model_pos + UPCOMING_MODEL_AMOUNT);
			score += furniture_count_old;
			std::cout << "Score: " << score << std::endl;
			std::cout << "Furniture_count_old in model (house excluded): " << furniture_count_old << std::endl;

		}
		// remember the position at which the new model was added
		last_model_pos = model_pos;
		collision_entities.push_front(main_character);

		collision::CheckCollisions(collision_entities);
		collision_entities.pop_front();
	}

	//manages the key input in the game scene
	void scene::In_Game_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			cv::destroyWindow("camera");
			return_value = scene::Scenes::STOP;
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			game_state = scene::Game_State::PAUSED;
		}
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		{
			game_state = scene::Game_State::RUNNING;
		}
	}

	void scene::In_Game_Scene::update_hand_detection()
	{
		reg_left.UpdateTime(delta_time);
		reg_right.UpdateTime(delta_time);
		reg_up.UpdateTime(delta_time);

		cv::Mat camera_frame;
		static_camera::getCap().read(camera_frame);
		reg_left.DetectHand(camera_frame);
		reg_right.DetectHand(camera_frame);
		reg_up.DetectHand(camera_frame);

		cv::imshow("camera", camera_frame);
	}

	void scene::In_Game_Scene::OnSkinCalibrationCallback()
	{
		calibrated = true;
		std::cout << "on skin calibration callback" << std::endl;
		std::vector<int> tresholds = reg_left.CalculateSkinTresholds();
		reg_right.setSkinTresholds(tresholds);
		reg_up.setSkinTresholds(tresholds);
	}

	//renders the models for the pause menu
	void In_Game_Scene::render_pause_menu()
	{
		render_engine::renderer::Render(pause_guis, *gui_shader);
	}

	void In_Game_Scene::DrawScore(int score)
	{
		std::vector<int> digits;
		score_guis.clear();

		toolbox::GetDigitsFromNumber(score, digits);


		for (int i = digits.size() - 1; i >= 0; i--)
		{
			score_textures[digits[i]].get()->position.x = 0.15 * i - 0.9; // place the number at the top left. the numbers are just fine tuned to get the position just right
			render_engine::renderer::Render(score_textures[digits[i]], *gui_shader);
		}
	}

	void In_Game_Scene::UpdateDeltaTime()
	{
		double current_time = glfwGetTime();
		static double last_frame_time = current_time;
		delta_time = current_time - last_frame_time;
		last_frame_time = current_time;

	}
}
