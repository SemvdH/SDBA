#include "static_shader.h"
#include "../toolbox/toolbox.h"

namespace shaders
{
	static std::string vertex_shader = R"(
	#version 400 core
	// The VertexShader is run for each vertex on the screen.


	// Position of the vertex
	in vec3 position;
	// Coordinates of the texture
	in vec2 texture_coords;

	// Equal to the texture_coords
	out vec2 pass_texture_coords;

	uniform mat4 model_matrix;
	uniform mat4 projection_matrix;
	uniform mat4 view_matrix;

	void main(void)
	{
		// Tell OpenGL where to render the vertex
		gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);

		// Pass the texture_coords directly to the fragment shader
		pass_texture_coords = texture_coords;
	}
	)";
	

	static std::string fragment_shader = R"(
	#version 400 core
	// The FragmentShader is run for each pixel in a face on the screen.


	// Interpolated textureCoordinates of the vertex (relative to the distance to each vertex)
	in vec2 pass_texture_coords;

	// Final color of the pixel
	out vec4 out_color;

	// The texture of the model
	uniform sampler2D texture_sampler;

	void main(void)
	{
		out_color = texture(texture_sampler, pass_texture_coords);
	}
	)";
	
	
	StaticShader::StaticShader(): ShaderProgram(vertex_shader, fragment_shader)
	{
	}

	void StaticShader::LoadModelMatrix(const glm::mat4& matrix) const
	{
		LoadMatrix(location_model_matrix, matrix);
	}

	void StaticShader::LoadProjectionMatrix(const glm::mat4& projection) const
	{
		LoadMatrix(location_projection_matrix, projection);
	}

	void StaticShader::LoadViewMatrix(entities::Camera& camera) const
	{
		const glm::mat4 view_matrix = toolbox::CreateViewMatrix(camera);
		LoadMatrix(location_view_matrix, view_matrix);
	}

	void StaticShader::SetAttributes() const
	{
		SetAttribute(0, "position");
		SetAttribute(1, "texture_coords");
	}

	void StaticShader::GetAllUniformLocations()
	{
		location_model_matrix = GetUniformLocation("model_matrix");
		location_projection_matrix = GetUniformLocation("projection_matrix");
		location_view_matrix = GetUniformLocation("view_matrix");
	}
}
