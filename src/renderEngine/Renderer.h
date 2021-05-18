#pragma once

#include "../entities/Entity.h"
#include "../shaders/StaticShader.h"

namespace renderEngine
{
	namespace renderer
	{
		/*
			Call this function when starting the program
		 */
		void Init(shaders::StaticShader& shader);
		
		/*
			Call this function before rendering. 
		*/
		void Prepare();

		/*
			Call this function when wanting to Render a mesh to the screen.
		*/
		void Render(entities::Entity& entity, shaders::StaticShader& shader);
	}
}