#pragma once

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace entities
{
	class Camera
	{
	private:
		float speed = 0.02f;
		
		glm::vec3 position;
		glm::vec3 rotation;

	public:
		Camera(const ::glm::vec3& position, const ::glm::vec3& rotation);

		void move(GLFWwindow* window);
		
		inline glm::vec3 getPosition() const{ return position; }
		inline glm::vec3 getRotation() const{ return rotation; }
	};
}