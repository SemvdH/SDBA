#pragma once

#include <string>
#include <vector>
#include "../models/model.h"

namespace render_engine
{
	namespace loader
	{
		/*
			This function generates a model from model data.
		*/
		struct models::RawModel LoadToVAO(std::vector<float>& positions, std::vector<float>& texture_coords, std::vector<unsigned int>& indices);

		/*
			Loads a texture from a file into openGL using stb_image.h
		 */
		GLuint LoadTexture(std::string file_name);
		
		/*
			Call this function when cleaning up all the meshes (when exiting the program).
		*/
		void CleanUp();
	}
}