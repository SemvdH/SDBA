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
		GLuint location_modelMatrix;
		GLuint location_projectionMatrix;
		GLuint location_viewMatrix;
		
	public:
		StaticShader();

		void loadModelMatrix(const glm::mat4& matrix) const;
		void loadProjectionMatrix(const glm::mat4& projection) const;
		void loadViewMatrix(entities::Camera& camera) const;
			
	protected:
		void setAttributes() const override;
		void getAllUniformLocations() override;
	};
}