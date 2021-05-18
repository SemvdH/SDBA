#pragma once

#include <GL/glew.h>

namespace models
{
	/*
		Structure for storing a vboID and vertexCount.

		This structure represents a Bare bones Model (A mesh without a texture).
		The vaoID, points to an ID stored by openGL and the
		vertexCount is how many triangles in the mesh there are.
	*/
	struct RawModel
	{
		GLuint vaoID;
		int vertexCount;
	};

	/*
		Structure for storing a texture (textureID) to apply to a RawModel.
	*/
	struct ModelTexture
	{
		GLuint textureID;
	};
	
	/*
		Structure for storing a RawModel and a Texure.

		This struct represents a model with a texture.
	*/
	struct TexturedModel
	{
		RawModel rawModel;
		ModelTexture texture;
	};
}