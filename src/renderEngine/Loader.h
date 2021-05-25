#pragma once

#include <string>
#include <vector>
#include "../models/model.h"

namespace render_engine
{
	namespace loader
	{
		/*
		*	@brief: This function generates a model from model data.
		*
		*	@param position: The positions of each vertex (in order: x, y, z) in the model
		*	@param texture_coords: The texture coordinates of the model
		*	@param normals: The normals of each face of the model
		*	@param indices: A list with a sort of lookup table to the positions parameter
		*
		*	@return: A new rawmodel which represents al the parameters in one struct
		*/
		models::RawModel LoadToVAO(std::vector<float>& positions, std::vector<float>& texture_coords, std::vector<float>& normals, std::vector<unsigned int>& indices);

		/*
		 * @brief: Overloaded function of the function above, but does not need normals and indices.
		 *         Use this function to for example load GUI items to OpenGL.
		 *
		 * @param position: The positions of each vertex (in order: x, y, z) in the model
		 *
		 * @return: A new rawmodel which represents al the parameters in one struct
		 */
		models::RawModel LoadToVAO(std::vector<float>& positions);
		
		/*
		*	@brief: Loads a texture from a file into openGL using stb_image.h
		*
		*	@param file_name: The filepath to the texture
		 */
		GLuint LoadTexture(std::string file_name);
		
		/*
		*	@brief: Call this function when cleaning up all the meshes (when exiting the program).
		*/
		void CleanUp();
	}
}