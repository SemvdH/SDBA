#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "shader_program.h"

namespace shaders
{
	/*
	 * This class handles the shaders for all the GUI items
	 */
	
	class GuiShader : public ShaderProgram
	{
	private:
		GLuint location_model_matrix;

	public:
		GuiShader();

		/*
		 * @brief: A method to load the model matrix into the shader
		 *
		 * @param matrix: The model matrix
		 */
		void LoadModelMatrix(const glm::mat4& matrix) const;

	protected:
		void SetAttributes() const override;
		void GetAllUniformLocations() override;
	};
}
