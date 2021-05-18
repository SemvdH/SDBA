#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <ostream>

#include "models/Model.h"
#include "renderEngine/loader.h"
#include "renderEngine/obj_loader.h"
#include "renderEngine/Renderer.h"
#include "shaders/static_shader.h"
#include "toolbox/math.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

static double UpdateDelta();

static GLFWwindow* window;


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

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
	    if (key == GLFW_KEY_ESCAPE)
	        glfwSetWindowShouldClose(window, true);
    });
	
	
    models::RawModel raw_model = LoadObjModel("res/Tree.obj");
    models::ModelTexture texture = { render_engine::loader::LoadTexture("res/TreeTexture.png") };
    models::TexturedModel model = { raw_model, texture };
    entities::Entity entity(model, glm::vec3(0, -5, -20), glm::vec3(0, 0, 0), 1);
	
    shaders::StaticShader shader;
    shader.Init();
    render_engine::renderer::Init(shader);

    entities::Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	
	// Main game loop
	while (!glfwWindowShouldClose(window))
	{
        // Update
        const double delta = UpdateDelta();
        entity.increaseRotation(glm::vec3(0, 1, 0));
        camera.move(window);

		// Render
        render_engine::renderer::Prepare();
        shader.Start();
        shader.LoadViewMatrix(camera);
		
        render_engine::renderer::Render(entity, shader);

		// Finish up
        shader.Stop();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up
    shader.CleanUp();
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