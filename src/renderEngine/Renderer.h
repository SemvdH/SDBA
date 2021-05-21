#pragma once

#include "../entities/entity.h"
#include "../shaders/entity_shader.h"

namespace render_engine
{
	namespace renderer
	{
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