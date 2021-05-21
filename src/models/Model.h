#pragma once

#include <GL/glew.h>

namespace models
{
	/*
		Structure for storing a vboID and vertex_count (this representa a mesh without a model).

		vao_id = The openGL id of the model
		vertex_count = The amount of vertices in the model
		model_size = The size on each axis of the model
	*/
	struct RawModel
	{
		GLuint vao_id;
		int vertex_count;
		glm::vec3 model_size;
	};

	/*
		Structure for storing a texture (texture_id) to apply to a RawModel.

		texture_id = The openGL id of the textures
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