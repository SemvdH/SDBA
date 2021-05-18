#pragma once

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderProgram.h"
#include "../entities/Camera.h"

/*
	This class does represents the shaders for the models.
 */

namespace shaders
{	
	class StaticShader : public ShaderProgram
	{
	private:
		GLuint location_model_matrix;
		GLuint location_projection_matrix;
		GLuint location_view_matrix;
		
	public:
		StaticShader();

		void LoadModelMatrix(const glm::mat4& matrix) const;
		void LoadProjectionMatrix(const glm::mat4& projection) const;
		void LoadViewMatrix(entities::Camera& camera) const;
			
	protected:
		void SetAttributes() const override;
		void GetAllUniformLocations() override;
	};
}