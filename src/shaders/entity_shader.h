#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "shader_program.h"
#include "../entities/camera.h"
#include "../entities/light.h"

/*
	This class handles the shaders for the entities.
 */

namespace shaders
{	
	class EntityShader : public ShaderProgram
	{
	private:
		GLuint location_model_matrix;
		GLuint location_projection_matrix;
		GLuint location_view_matrix;
		GLuint location_light_position;
		GLuint location_light_color;
		GLuint location_shine_damper;
		GLuint location_reflectivity;
		GLuint location_sky_color;
		
	public:
		EntityShader();

		/*
		 * @brief: A method to load the model matrix into the shader
		 *
		 * @param matrix: The model matrix
		 */
		void LoadModelMatrix(const glm::mat4& matrix) const;

		/*
		 * @brief: A method to load the projection matrix into the shader
		 *
		 * @param projection: The projection matrix
		 */
		void LoadProjectionMatrix(const glm::mat4& projection) const;

		/*
		 * @brief: A method to load the view matrix (camera) into the shader
		 *
		 * @param camera: The camera which the scene needs to be rendered from
		 */
		void LoadViewMatrix(entities::Camera& camera) const;

		/*
		 * @brief: A method to load a light into the shader
		 *
		 * @param light: The light
		 */
		void LoadLight(entities::Light& light) const;

		/*
		 * @brief: A method to load the the shine variables from a model into the shader
		 *
		 * @param shine_damper: The dampening of the angle from when to render reflectivity on the vertex
		 * @param reflectivity: The amount the model reflects
		 */
		void LoadShineVariables(float shine_damper, float reflectivity) const;

		/*
		 * @brief: A method to load the sky color into the shader. This color will be used for the fog
		 *
		 * @param sky_color: The color of the sky
		 */
		void LoadSkyColor(glm::vec3 sky_color) const;
			
	protected:
		void SetAttributes() const override;
		void GetAllUniformLocations() override;
	};
}