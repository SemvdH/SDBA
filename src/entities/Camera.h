#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace entities
{
	/*
	 * This class represents the viewport of the game. The whole game is seen through this class
	 */
	
	class Camera
	{
	private:
		// The movement speed of the camera
		const float SPEED = 0.5f;
		const float UP_SPEED = 0.9f;
		
		glm::vec3 position;
		glm::vec3 rotation;

	public:
		Camera(const ::glm::vec3& position, const ::glm::vec3& rotation);

		/*
		 * @brief: This funtion moves the camera's position from the inputs of the keyboard
		 *
		 * @param window: The OpenGL window
		 */
		void Move(GLFWwindow* window);
		
		inline glm::vec3 GetPosition() const{ return position; }
		inline glm::vec3 GetRotation() const{ return rotation; }
	};
}