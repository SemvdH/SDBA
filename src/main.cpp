#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
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

#include "computervision/MenuTest.h"
#include "computervision/ObjectDetection.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

static double UpdateDelta();

static GLFWwindow* window;
int chosen_item = 0;
scene::Scene* current_scene;

int main(void)
{
#pragma region OPENGL_SETTINGS
	if (!glfwInit())
		throw "Could not inditialize glwf";
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGT, "SDBA", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);
	glewInit();
	glGetError();
#pragma endregion

    
    current_scene = new scene::Startup_Scene();

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE)
            {
                glfwSetWindowShouldClose(window, true);
            }
    	
            current_scene->onKey(window, key, scancode, action, mods);
        });

    bool window_open = true;

	computervision::ObjectDetection objDetect;
	cv::Mat cameraFrame;

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

            case scene::Scenes::STARTUP:
                current_scene = new scene::Startup_Scene();
                break;

		
            case scene::Scenes::INGAME:
                current_scene = new scene::In_Game_Scene();
                break;
                
            default:
                std::cout << "Wrong return value!!! ->" << std::endl;
                break;
        }
        
		
		////////////////////////// KIMS SHIT ////////////////////////////////////
		cameraFrame = objDetect.readCamera();
		computervision::MenuTest menu_test;

		//Get hand state from camera
		bool hand_detection = objDetect.detectHand(cameraFrame);
		
		if (hand_detection) 
		{
			std::cout << "hand is opened" << std::endl;
			
			//Loop through menu items
			chosen_item = menu_test.GetMenuItem(true);

			//For debug only, to see if chosen item is selected properly when hand is opened
			std::cout << "chosen item: " << chosen_item << std::endl;
			
		}
		else if (!hand_detection) 
		{
			//for debug only, to see if the chosen item is selected properly when hand is closed
			std::cout << "hand is closed" << std::endl;
			//std::cout << "item to start: " << chosen_item << std::endl;

			//TODO link chosen item to the correct game states
			switch (chosen_item)
			{
				case 1:
					//Game state 0
					std::cout << "in case: " << chosen_item << std::endl;
					break;
				case 2:
					//Game state 1
					std::cout << "in case: " << chosen_item << std::endl;
					break;
				case 3:
					//Game state 2
					std::cout << "in case: " << chosen_item << std::endl;
					break;
				case 4:
					//Game state 3
					std::cout << "in case: " << chosen_item << std::endl;
				default:
				break;
			}
		}

		///////////////////////// END OF KIMS SHIT ///////////////////////////////

		// Finish up
		//shader.Stop();
		glfwSwapBuffers(window);
		glfwPollEvents();
           
	}

	// Clean up -> preventing memory leaks!!!
    std::cout << "ending..." << std::endl;
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
