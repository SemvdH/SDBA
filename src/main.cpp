#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <map>

#include "stb_image.h"
#include <ostream>
#include <stdlib.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

#include "collision/collision.h"
#include "gui/gui_interactable.h"
#include "models/model.h"
#include "renderEngine/loader.h"
#include "renderEngine/obj_loader.h"
#include "renderEngine/renderer.h"
#include "shaders/entity_shader.h"
#include "toolbox/toolbox.h"
#include "scenes/scene.h"
#include "scenes/in_Game_Scene.h"
#include "scenes/startup_Scene.h"
#include "scenes/loading_Scene.h"
#include "model_Storage.h"

#include "computervision/object_detection.h"
#include "scenes/game_Over_Scene.h"
#include "entities/collision_entity.h"
#include "computervision/object_detection.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

int score;
static double UpdateDelta();

static GLFWwindow* window;

scene::Scene* current_scene;

bool points_img_available = false;
cv::Mat points_img;

int main(void)
{
#pragma region OPENGL_SETTINGS
	if (!glfwInit())
		throw "Could not inditialize glwf";
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SDBA", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);
	glewInit();
	glGetError();
#pragma endregion
    //current_scene = new scene::Startup_Scene();
    current_scene = new scene::Loading_Scene();
    score = 0;


    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE)
            {
                glfwSetWindowShouldClose(window, true);
            }
    	
            current_scene->onKey(window, key, scancode, action, mods);
        });
    
    bool window_open = true;

	// Main game loop
	while (!glfwWindowShouldClose(window) && window_open)
	{
        //Update
        const double delta = UpdateDelta();

        scene::Scenes return_value = current_scene->start(window);
        delete current_scene;

        switch (return_value) {
            case scene::Scenes::STOP:
                window_open = false;
                break;

            case scene::Scenes::LOADING:
                current_scene = new scene::Loading_Scene();
                break;

            case scene::Scenes::STARTUP:
                current_scene = new scene::Startup_Scene();
                break;

		
            case scene::Scenes::INGAME:
                current_scene = new scene::In_Game_Scene(&score);
                break;
                
            case scene::Scenes::GAMEOVER:
                current_scene = new scene::Game_Over_Scene(score);
                break;

            default:
                std::cout << "Wrong return value!!! ->" << std::endl;
                break;
        }
        
		// Finish up
		//shader.Stop();
		glfwSwapBuffers(window);
		glfwPollEvents();
           
	}

	// Clean up -> preventing memory leaks!!!
    std::cout << "ending..." << std::endl;
    render_engine::loader::CleanUp();
	glfwTerminate();
	return 0;
}

static double UpdateDelta()
{
	double current_time = glfwGetTime();
	static double last_frame_time = current_time;
	double delt_time = current_time - last_frame_time;
	last_frame_time = current_time;
	return delt_time;
}