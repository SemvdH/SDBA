#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "shader_program.h"
#include "../entities/camera.h"
#include "../entities/light.h"

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
		GLuint location_light_position;
		GLuint location_light_color;
		GLuint location_shine_damper;
		GLuint location_reflectivity;
		
	public:
		StaticShader();

		void LoadModelMatrix(const glm::mat4& matrix) const;
		void LoadProjectionMatrix(const glm::mat4& projection) const;
		void LoadViewMatrix(entities::Camera& camera) const;

		void LoadLight(entities::Light& light) const;
		void LoadShineVariables(float shine_damper, float reflectivity) const;
			
	protected:
		void SetAttributes() const override;
		void GetAllUniformLocations() override;
	};
}