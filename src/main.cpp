#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <map>

#include "stb_image.h"
#include <ostream>

#include <opencv2/core.hpp>

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

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

static double UpdateDelta();

static GLFWwindow* window;
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
            current_scene->onKey(window, key, scancode, action, mods);
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
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
	}

	// Clean up -> preventing memory leaks!!!
    std::cout << "ending..." << std::endl;
    delete current_scene;
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
