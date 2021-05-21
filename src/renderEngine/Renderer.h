#pragma once

#include "../entities/entity.h"
#include "../shaders/entity_shader.h"

namespace render_engine
{
	namespace renderer
	{
		const glm::vec3 SKY_COLOR = { 0.3f, 0.4f, 0.6f };
		
		/*
			Call this function when starting the program
		 */
		void Init(shaders::EntityShader& shader);
		
		/*
			Call this function before rendering. 
		*/
		void Prepare();

		/*
			Call this function when wanting to Render a mesh to the screen.
		*/
		void Render(entities::Entity& entity, shaders::EntityShader& shader);
	}
}