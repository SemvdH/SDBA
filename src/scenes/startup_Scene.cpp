#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "startup_Scene.h"
#include "../computervision/ObjectDetection.h"
#include "../computervision/HandDetectRegion.h"
#include <iostream>

namespace scene
{
	std::vector<computervision::HandDetectRegion> regions;
	computervision::ObjectDetection objDetect;
	computervision::HandDetectRegion reg1("left",20,100,150,150);
	computervision::HandDetectRegion reg2("right",200,200,150,150);

	scene::Scenes scene::Startup_Scene::start(GLFWwindow *window)
	{
		regions.push_back(reg1);
		regions.push_back(reg2);
		while (return_value == scene::Scenes::STARTUP)
		{
			render();
			update(window);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		return return_value;
	}

	void scene::Startup_Scene::render() 
	{

	}

	void scene::Startup_Scene::update(GLFWwindow* window)
	{
		cv::Mat camera_frame = objDetect.ReadCamera();
		reg1.DetectHand(camera_frame);
		reg2.DetectHand(camera_frame);

		cv::imshow("camera", camera_frame);

		int key = cv::waitKey(1);

		if (key == 98) // b, calibrate the background
		{
			for (int i = 0; i < regions.size(); i++)
			{
				regions[i].CalibrateBackground();
			}
		}
		else if (key == 115) // s, calibrate the skin color
		{
			std::vector<int> tresholds = regions[0].CalculateSkinTresholds();
			for (int i = 1; i < regions.size(); i++)
			{
				regions[i].setSkinTresholds(tresholds);
			}

		}

	}

	void scene::Startup_Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			return_value = scene::Scenes::INGAME;
		}
	}
}
