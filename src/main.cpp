#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include "stb_image.h"
#include <ostream>

#include <opencv2/core.hpp>

#include "models/model.h"
#include "renderEngine/loader.h"
#include "renderEngine/obj_loader.h"
#include "renderEngine/renderer.h"
#include "shaders/entity_shader.h"
#include "toolbox/toolbox.h"

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
	
	
    models::RawModel raw_model = render_engine::LoadObjModel("res/House.obj");
    models::ModelTexture texture = { render_engine::loader::LoadTexture("res/Texture.png") };
    texture.shine_damper = 10;
    texture.reflectivity = 0;
    models::TexturedModel model = { raw_model, texture };

    /**
    * load and add some models (in this case some level sections) to the entities list.
    * */
    std::vector<entities::Entity> entities;
    int z = 0;
    for (int i = 0; i < 5; ++i)
    {
        entities.push_back(entities::Entity(model, glm::vec3(0, -50, -50 - z), glm::vec3(0, 90, 0), 20));
        z += (raw_model.model_size.x * 20);
    }

    std::vector<entities::Light> lights;
    lights.push_back(entities::Light(glm::vec3(0, 1000, -7000), glm::vec3(5, 5, 5)));
    lights.push_back(entities::Light(glm::vec3(0, 0, -30), glm::vec3(2, 0, 2), glm::vec3(0.0001f, 0.0001f, 0.0001f)));
    lights.push_back(entities::Light(glm::vec3(0, 0, -200), glm::vec3(0, 2, 0), glm::vec3(0.0001f, 0.0001f, 0.0001f)));

	shaders::EntityShader shader;
    shader.Init();
    render_engine::renderer::Init(shader);

    entities::Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));


	// GUI stuff
    shaders::GuiShader gui_shader;
    gui_shader.Init();
	
    std::vector<gui::GuiTexture*> guis;
    gui::Button button(render_engine::loader::LoadTexture("res/Mayo.png"), glm::vec2(0.5f, 0.0f), glm::vec2(0.25f, 0.25f));
    button.SetHoverTexture(render_engine::loader::LoadTexture("res/Texture.png"));
    button.SetClickedTexture(render_engine::loader::LoadTexture("res/Mayo.png"));
    guis.push_back(&button);
	
	
	// Main game loop
	while (!glfwWindowShouldClose(window))
	{
        // Update
        const double delta = UpdateDelta();
        camera.Move(window);

        button.Update(window);

		// Render
        render_engine::renderer::Prepare();
		
        shader.Start();
        shader.LoadSkyColor(render_engine::renderer::SKY_COLOR);
        shader.LoadLights(lights);
        shader.LoadViewMatrix(camera);
		
        // Renders each entity in the entities list
		for (entities::Entity& entity : entities)
		{
            render_engine::renderer::Render(entity, shader);
		}

		// Stop rendering the entities
        shader.Stop();

		
        // Render GUI items
        render_engine::renderer::Render(guis, gui_shader);

        // Finish up
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up
    shader.CleanUp();
    gui_shader.CleanUp();
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