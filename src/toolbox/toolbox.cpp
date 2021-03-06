#include <ctime>
#include "toolbox.h"
#include <iostream>
namespace toolbox
{
	glm::mat4 CreateModelMatrix(glm::vec2 translation, glm::vec2 scale)
	{
		glm::mat4 matrix(1.0f);
		matrix = glm::translate(matrix, glm::vec3(translation.x, translation.y, 0));
		matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, 0));
		return matrix;
	}

	glm::mat4 CreateModelMatrix(glm::vec3 translation, glm::vec3 rotation, float scale)
	{
		glm::mat4 matrix(1.0f);
		matrix = glm::translate(matrix, translation);
		matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
		return matrix;
	}

	glm::mat4 CreateViewMatrix(entities::Camera& camera)
	{
		glm::mat4 matrix(1.0f);
		matrix = glm::rotate(matrix, glm::radians(camera.GetRotation().x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(camera.GetRotation().y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(camera.GetRotation().z), glm::vec3(0, 0, 1));
		const glm::vec3 negative_cam_pos = glm::vec3(-camera.GetPosition().x, -camera.GetPosition().y, -camera.GetPosition().z);
		matrix = glm::translate(matrix, negative_cam_pos);
		return matrix;
	}
		float Lerp(float from, float to, float amount)
	{
		return from + amount * (to - from);
	}

	glm::vec3 Lerp(glm::vec3 from, glm::vec3 to, float amount)
	{
		glm::vec3 final;
		final.x = Lerp(from.x, to.x, amount);
		final.y = Lerp(from.y, to.y, amount);
		final.z = Lerp(from.z, to.z, amount);
		return final;
  }
  
	int Random(const int min, const int max)
	{
		static bool first = true;
		if (first)
		{
			srand(time(0));
			first = false;
		}
		return min + rand() % ((max + 1) - min);
	}

	void GetDigitsFromNumber(int number, std::vector<int>& result_vector)
	{
		if (number >= 10)
			GetDigitsFromNumber(number / 10, result_vector);

		result_vector.push_back(number % 10);
	}
}
