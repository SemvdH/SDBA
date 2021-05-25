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
			const glm::mat4 projectionMatrix = 
				glm::perspective(glm::radians(FOV), (float)(WINDOW_WIDTH / WINDOW_HEIGT), NEAR_PLANE, FAR_PLANE);
			
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
			const models::RawModel rawModel = model.raw_model;

			// Enable the model
			glBindVertexArray(rawModel.vao_id);

			// Enable the inputs for the vertexShader
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			// Load the transformation of the model into the shader
			const glm::mat4 modelMatrix = toolbox::CreateModelMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale());
			shader.LoadModelMatrix(modelMatrix);
			
			// Draw the model
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model.texture.texture_id);
			glDrawElements(GL_TRIANGLES, rawModel.vertex_count, GL_UNSIGNED_INT, 0);
			
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glBindVertexArray(0);
		}
	}
}