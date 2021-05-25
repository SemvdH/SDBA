#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../models/model.h"
#include "loader.h"
#include "../toolbox/toolbox.h"
#include "renderer.h"

#include <iostream>

namespace render_engine
{
	namespace renderer
	{
		static const float FOV = 70.0f;
		static const float NEAR_PLANE = 0.01f;
		static const float FAR_PLANE = 1000.0f;

		// GUI variables
		static models::RawModel quad;
		
		
		void Init(shaders::EntityShader& shader)
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

			// Initialize the quad for the GUI
			std::vector<float> quad_positions = { -1, 1, -1, -1, 1, 1, 1, -1 };
			quad = loader::LoadToVAO(quad_positions);
		}

		/*
		 	This function will clear the screen.
		*/
		void Prepare()
		{
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(SKY_COLOR.r, SKY_COLOR.g, SKY_COLOR.b, 1.0f);
		}

		/*
			This function will Render a Model on the screen.
		*/
		void Render(entities::Entity& entity, shaders::EntityShader& shader)
		{
			const models::TexturedModel model = entity.GetModel();
			const models::RawModel raw_model = model.raw_model;
			const models::ModelTexture texture = model.texture;

			// Enable the model (VAO)
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

			// Disable the VBO's and model (VAO)
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindVertexArray(0);
		}

		void Render(std::vector<gui::GuiTexture>& guis, shaders::GuiShader& shader)
		{
			shader.Start();
			
			// Enable the VAO and the positions VBO
			glBindVertexArray(quad.vao_id);
			glEnableVertexAttribArray(0);

			// Enable alpha blending (for transparency in the texture)
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Disable depth testing to textures with transparency can overlap
			glDisable(GL_DEPTH_TEST);
			
			// Render each gui to the screen
			for (gui::GuiTexture& gui : guis)
			{
				// Bind the texture of the gui to the shader
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, gui.texture);

				glm::mat4 matrix = toolbox::CreateModelMatrix(gui.position, gui.scale);
				shader.LoadModelMatrix(matrix);
				
				glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.vertex_count);
			}

			// Enable depth test again
			glEnable(GL_DEPTH_TEST);
			
			// Disable alpha blending
			glDisable(GL_BLEND);
			
			// Disable the VBO and VAO
			glDisableVertexAttribArray(0);
			glBindVertexArray(0);

			shader.Stop();
		}
	}
}
