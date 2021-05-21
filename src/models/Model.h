#pragma once

#include <GL/glew.h>

namespace models
{
	/*
		Structure for storing a vboID and vertex_count.

		This structure represents a Bare bones Model (A mesh without a texture).
		The vao_id, points to an ID stored by openGL and the
		vertex_count is how many triangles in the mesh there are.
	*/
	struct RawModel
	{
		GLuint vao_id;
		int vertex_count;
	};

	/*
		Structure for storing a texture (texture_id) to apply to a RawModel.
	*/
	struct ModelTexture
	{
		GLuint texture_id;
	};
	
	/*
		Structure for storing a RawModel and a Texure.

		This struct represents a model with a texture.
	*/
	struct TexturedModel
	{
		RawModel raw_model;
		ModelTexture texture;
	};
}