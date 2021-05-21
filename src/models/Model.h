#pragma once

#include <GL/glew.h>

namespace models
{
	/*
		Structure for storing a vboID and vertex_count.

		This structure represents a Bare bones Model (A mesh without a texture).
		The vao_id, points to an ID stored by openGL and the
		vertex_count is how many triangles in the mesh there are.

		model_size is a vec3 that contains the size of the loaded model.
	*/
	struct RawModel
	{
		GLuint vao_id;
		int vertex_count;
		glm::vec3 model_size;
	};

	/*
		Structure for storing a texture (texture_id) to apply to a RawModel.

		shine_damper = A damper for the angle the model needs to be look at to see reflections
		reflectivity = The amount of light the model reflects
	*/
	struct ModelTexture
	{
		GLuint texture_id;
		float shine_damper = 1;
		float reflectivity = 0;
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