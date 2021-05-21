#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../models/model.h"
#include "renderer.h"
#include "../toolbox/toolbox.h"

namespace render_engine
{
	namespace renderer
	{
		static const float FOV = 70.0f;
		static const float NEAR_PLANE = 0.01f;
		static const float FAR_PLANE = 1000.0f;

		/*
			This function will load the projectionMatrix into the shader
		 */
		void Init(shaders::StaticShader& shader)
		{
			// Faces which are not facing the camera are not rendered
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			
			const glm::mat4 projectionMatrix = 
				glm::perspective(glm::radians(FOV), (WINDOW_WIDTH / WINDOW_HEIGT), NEAR_PLANE, FAR_PLANE);

			// Load the projectionmatrix into the shader
			shader.Start();
			shader.LoadProjectionMatrix(projectionMatrix);
			shader.Stop();
		}

		/*
		 	This function will clear the screen.
		*/
		void Prepare()
		{
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
		}

		/*
			This function will Render a Model on the screen.
		*/
		void Render(entities::Entity& entity, shaders::StaticShader& shader)
		{
			const models::TexturedModel model = entity.GetModel();
			const models::RawModel raw_model = model.raw_model;
			const models::ModelTexture texture = model.texture;

			// Enable the model
			glBindVertexArray(raw_model.vao_id);

			// Enable the VBO's from the model (VAO)
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			// Load the transformation of the model into the shader
			const glm::mat4 modelMatrix = toolbox::CreateModelMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale());
			shader.LoadModelMatrix(modelMatrix);
			shader.LoadShineVariables(texture.shine_damper, texture.reflectivity);
			
			// Draw the model
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model.texture.texture_id);
			glDrawElements(GL_TRIANGLES, raw_model.vertex_count, GL_UNSIGNED_INT, 0);

			// Disable the VBO's and model
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindVertexArray(0);
		}
	}
}