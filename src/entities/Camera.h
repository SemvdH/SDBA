#pragma once

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace entities
{
	class Camera
	{
	private:
		const float SPEED = 0.02f;
		
		glm::vec3 position;
		glm::vec3 rotation;

	public:
		Camera(const ::glm::vec3& position, const ::glm::vec3& rotation);

		void Move(GLFWwindow* window);
		
		inline glm::vec3 GetPosition() const{ return position; }
		inline glm::vec3 GetRotation() const{ return rotation; }
	};
}