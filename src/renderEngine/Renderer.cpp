#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "../models/Model.h"
#include "Renderer.h"
#include "../toolbox/Toolbox.h"

namespace renderEngine
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
				glm::perspective(glm::radians(FOV), (WINDOW_WIDTH / WINDOW_HEIGT), NEAR_PLANE, FAR_PLANE);
			
			shader.start();
			shader.loadProjectionMatrix(projectionMatrix);
			shader.stop();
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
			const models::TexturedModel model = entity.getModel();
			const models::RawModel rawModel = model.rawModel;

			// Enable the model
			glBindVertexArray(rawModel.vaoID);

			// Enable the inputs for the vertexShader
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			// Load the transformation of the model into the shader
			const glm::mat4 modelMatrix = toolbox::createModelMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
			shader.loadModelMatrix(modelMatrix);
			
			// Draw the model
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model.texture.textureID);
			glDrawElements(GL_TRIANGLES, rawModel.vertexCount, GL_UNSIGNED_INT, 0);
			
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glBindVertexArray(0);
		}
	}
}