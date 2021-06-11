#pragma once

#include <memory>
#include "../gui/gui_element.h"
#include "../entities/entity.h"
#include "../shaders/entity_shader.h"
#include "../shaders/gui_shader.h"

namespace render_engine
{
	namespace renderer
	{
		const glm::vec3 SKY_COLOR = { 0.3f, 0.4f, 0.6f };
		
		/*
			@brief: Call this function when starting the program

			@param shader: The shader to render the entities with
		 */
		void Init(shaders::EntityShader& shader);
		
		/*
			@brief: Call this function before rendering.
					This function will enable culling and load the projectionMatrix into the shader.
		*/
		void Prepare();

		/*
			@brief: Call this function when wanting to Render a mesh to the screen.

			@param entity: The entity which needs to be rendered
			@param shader: The shader the entity needs to be rendered with
		*/
		void Render(std::shared_ptr<entities::Entity> entity, shaders::EntityShader& shader);

		/*
			@brief: Call this function to render gui_textures on the screen

			@param guis:  A list with all the GUI textures you want to render
			@param shade: The shader the GUI textures need to be rendered with
		 */
		void Render(std::vector<gui::GuiTexture*>& guis, shaders::GuiShader& shader);
	}
}